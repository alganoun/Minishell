/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/08/25 15:27:40 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_process(t_token *token, t_shell **shell)
{
	int	fdd;

	fdd = dup(0);
	if (ft_strcmp(token->cmd, "exit") == 0 && !token->next)
		exit_cmd(token);
	else if (token->next == NULL)
		choose(token, shell, FALSE);
	while (token->next)
	{
		while (token->out || token->in)
		{
			fdd = fork_process(token, shell, fdd);
			if (token->in)
				token->in -= 1;
			if (token->out)
				token = token->next->next;
		}
	}
	close(fdd);
	return (TRUE);
}

void	exec_builtin(t_token *token, t_shell **shell)
{
	if (ft_strcmp(token->cmd, "exit") == 0)
		exit_prog(&token, NULL, token->ret);
	else if (ft_strcmp(token->cmd, "echo") == 0)
		echo_process(token, (*shell)->env);
	else if (ft_strcmp(token->cmd, "cd") == 0)
		cd_process(token, &(*shell)->env);
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		pwd_process();
	else if (ft_strcmp(token->cmd, "export") == 0)
		export_process(token, &(*shell)->env);
	else if (ft_strcmp(token->cmd, "unset") == 0)
		unset_process(token, &(*shell)->env);
	else if (ft_strcmp(token->cmd, "env") == 0)
		env_process((*shell)->env);
	else if (ft_strcmp(token->cmd, "minishell") == 0)
		version_process(token);
	return ;
}

int	is_builtin(t_token *token)
{
	if (ft_strcmp(token->cmd, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "minishell") == 0)
		return (TRUE);
	return (FALSE);
}

void	choose(t_token *token, t_shell **shell, int pipe)
{
	if (token->redir)
		redirection(token, shell, pipe);
	else
		execution(token, shell, pipe);
}

void	execution(t_token *token, t_shell **shell, int pipe)
{
	quote_remover(&token->cmd, &token);
	if (token->exp == 0)
		get_variable_value(&token->cmd, (*shell)->env);
	if (is_builtin(token) == FALSE && pipe == TRUE)
		exec_cmd(token, shell);
	else if (is_builtin(token) == FALSE && pipe == FALSE)
		exec_cmd_fork(token, shell);
	else
		exec_builtin(token, shell);
}
