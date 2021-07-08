/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/07 12:45:13 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	printf_all(t_token *token) // Il faut supprimer cette fonction avant le rendu
{
	while (token != NULL)
	{
		printf("CMD : %s\n", token->cmd);
		printf("OPERATOR : %s\n", token->operator);
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
		printf("\n");
		token = token->next;
	}
}

int		input_process2(char **pre_token, t_token **token)
{
	int i;
	t_token *new;

	i = 1;
	(*token)->cmd = pre_token[0];
	while (pre_token[i] != NULL)
	{
		if (operator_finder(pre_token[i], token) == 1)
		{
			i++;
			init_struct(&new);
			new->next = (*token)->next->next;
			(*token)->next->next = new;
			new->cmd = pre_token[i];
			*token = new;
		}
		else
		{
			option_finder(pre_token[i], token);
			arg_finder(pre_token[i], token);
		}
		i++;
	}
	return (0);
}

int		input_process(char **tab, t_token **token)
{
	int i;
	int j;

	i = 0;
	char **pre_token;
	(void)token;
	while (tab[i] != NULL)
	{
		j = 0;
		space_into_dot(&tab[i]);
		pre_token = ft_split(tab[i], '.');
		input_process2(pre_token, token);
		i++;
	}
	return (0);
}

int		parsing(char *line, t_token **token_list)
{
	int		i;
	char	**tab;
	t_token	*new;
	i = 0;

	tab = ft_split(line, ';');
	if (!tab)
		return (write_errors(3, NULL));
	while (i < tablen(tab))
	{
		init_struct(&new);
		token_add_back(token_list, &new);
		input_process(tab, &new);
		// Gérer les erreurs de mauvais char ici.
		i++;
	}
	return(0);
}

void	piping(t_token **token)
{
	if ((*token)->out == 1)
	{
		(*token)->in = 1;
		(*token)->out = 0;
	}
	if ((*token)->next && strncmp((*token)->next->operator, "|", 2) == 0)
		(*token)->out = 1;
}

void	exit_status(t_token **token)
{
	int i;
	int wstatus;
	int wret;

	i = 0;
	while (*token && i < (*token)->pid_index)
	{
		waitpid((*token)->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			wret = WEXITSTATUS(wstatus);
		(*token)->pids[i] = 0;
		i++;
	}
}

int		minishell(char **env)
{
	int ret;
	char *line;
	t_token *token;

	ret = 1;
	token = NULL;
	line = NULL;
	while(ret != 0)
	{
		get_next_input(&line);
		if (parsing(line, &token) == -1)
			return(exit_free(&token, &line));
		if (token != NULL)
		{
			piping(&token);
			printf_all(token);
			ret = cmd_selector(token, env);
			free_struct(&token);
		}
	}
	exit_status(&token);
	safe_free(&line);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	if (display_txt("banner.txt") == -1)
		return (-1);
	if (minishell(env) == -1)
		return (-1); // imprimer un message d'erreur ici
	return (0);
}
