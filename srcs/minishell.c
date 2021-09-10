/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/09/10 18:06:48 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_all(t_token *token) // Il faut supprimer cette fonction avant le rendu
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
	int	i;
	int	lenght;

	i = 0;
	lenght = tablen(old_env);
	(*shell) = ft_malloc(sizeof(t_shell));
	(*shell)->env = ft_malloc((lenght + 1) * sizeof(char *));
	while (old_env[i] != NULL)
	{
		(*shell)->env[i] = ft_strdup(old_env[i]);
		i++;
	}
	(*shell)->env[i] = NULL;
}

void	piping(t_token **token)
{
	t_token	*tmpA;
	t_token	*tmpB;

	if ((*token)->next)
	{
		tmpA = (*token);
		tmpB = (*token)->next;
		while (tmpB->next)
		{
			if (tmpB->operator && strncmp(tmpB->operator, "|", 1) == 0)
			{
				tmpA->out = 1;
				tmpB->next->in = 1;
			}
			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}
	}
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
		get_next_input(&line, (*shell)->env);
		if (ft_strlen(line) > 0 && parsing(&line, &token, (*shell)->env) != -1
			&& token->cmd != NULL)
		{
			piping(&token);
			//printf_all(token);
			ret = run_process(token, shell);
			free_struct(&token);
		}
	}
	exit_prog(&token, NULL, g_sig.exit_status);
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
	free_env(&shell);
	return (0);
}
