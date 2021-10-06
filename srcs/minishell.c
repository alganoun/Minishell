/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/06 04:23:55 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    printf_all(t_token *token) // Il faut supprimer cette fonction avant le rendu
{
    while (token != NULL)
    {
        printf("CMD : %s\n", token->cmd);
        printf("OPERATOR : %s\n", token->operator);
        if (token->redir != NULL)
            for (int i = 0 ; token->redir[i] != NULL ; i++)
                printf("REDIR = %s\n", token->redir[i]);
        else
            printf("REDIR = NULL\n");
        if (token->option != NULL)
            for (int i = 0 ; token->option[i] != NULL ; i++)
                printf("OPTION = %s\n", token->option[i]);
        else
            printf("OPTION = NULL\n");
        if (token->arg != NULL)
            for (int i = 0 ; token->arg[i] != NULL ; i++)
                printf("ARG = %s\n", token->arg[i]);
        else
            printf("arg = NULL\n");
        if (token->in)
            printf("IN = %d\n", token->in);
        else
            printf("IN = NULL\n");
        if (token->out)
            printf("OUT = %d\n", token->out);
        else
            printf("OUT = NULL\n");
        printf("\n");
        token = token->next;
    }
}

void	init_shell(char **old_env, t_shell **shell)
{
	int		i;
	int		j;
	int		lenght;
	char	*tmp;

	i = 0;
	j = 0;
	lenght = tablen(old_env) - 1;
	(*shell) = ft_malloc(sizeof(t_shell));
	(*shell)->env = ft_malloc((lenght + 1) * sizeof(char *));
	while (old_env[i] != NULL)
	{
		tmp = set_shlvl(old_env[i]);
		if (ft_strncmp("SHLVL=", old_env[i], 6) == 0)
			(*shell)->env[j++] = ft_strjoin("SHLVL=", tmp);
		else if (ft_strncmp("OLDPWD=", old_env[i], 7) != 0)
			(*shell)->env[j++] = ft_strdup(old_env[i]);
		safe_free(&tmp);
		i++;
	}
	(*shell)->env[j] = NULL;
}

void	piping(t_token **token)
{
	t_token	*tmpa;
	t_token	*tmpb;

	if ((*token)->next)
	{
		tmpa = (*token);
		tmpb = (*token)->next;
		while (tmpb->next)
		{
			if (tmpb->operator && strncmp(tmpb->operator, "|", 1) == 0)
			{
				tmpa->out = 1;
				tmpb->next->in = 1;
			}
			tmpa = tmpa->next;
			tmpb = tmpb->next;
		}
	}
}

void	search_for_heredoc(t_token *token)
{
	int	i;

	while (token)
	{
		i = 0;
		while (token->redir && token->redir[i]
			&& ft_strncmp(token->redir[i], "<<", 3) == 0)
		{
			if (token->std > 2)
				close(token->std);
			token->std = heredoc(token, token->redir[i + 1]);
			i += 2;
		}
		token = token->next;
	}
}

int	parsing(char **line, t_token **token_list, char **env)
{
	int		i;
	t_token	*new;

	i = 0;
	if (*token_list != NULL)
		free_struct(token_list);
	init_struct(&new);
	token_add_back(token_list, &new);
	if (input_process(line, &new, env) == -1)
		return (-1);
	safe_free(line);
	search_for_heredoc(*token_list);
	return (0);
}

void	minishell(t_shell **shell)
{
	int		ret;
	char	*line;
	t_token	*token;

	ret = 1;
	token = NULL;
	line = NULL;
	while (ret != 0)
	{
		g_sig.cmd = 0;
		g_sig.sigquit = g_sig.exit_status;
		get_next_input(&line, (*shell)->env);
		if (ft_strlen(line) > 0 && parsing(&line, &token, (*shell)->env) != -1
			&& token->cmd != NULL)
		{
			g_sig.cmd = 1;
			g_sig.exit_status = -1;
			printf_all(token);
			piping(&token);
			ret = run_process(token, shell);
			free_struct(&token);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, sigint);
	signal(SIGINT, sigint);
	init_shell(env, &shell);
	if (display_txt("banner.txt") == -1)
		return (-1);
	minishell(&shell);
	exit(g_sig.exit_status);
	return (0);
}
