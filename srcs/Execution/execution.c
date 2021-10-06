/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:39 by musoufi           #+#    #+#             */
/*   Updated: 2021/10/06 15:03:36 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end_exec(char ***cmd, char ***tab)
{
	(void)tab;
	free_tab(cmd);
	free_tab(tab);
	wait(&g_sig.pid);
	status_child();
}

void	exec_cmd(t_token *token, t_shell **shell)
{
	int			i;
	char		**tab;
	char		**cmd;
	struct stat	buf;

	i = 0;
	tab = check_bin(token, shell);
	cmd = build_cmd(token);
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		if (stat(tab[i], &buf) == 0)
			execve(tab[i], cmd, (*shell)->env);
		i++;
	}
	fd_write_errors(token);
	exit_prog(&token, NULL, -1);
}

void	exec_cmd_fork(t_token *token, t_shell **shell)
{
	int			i;
	char		**tab;
	char		**cmd;
	struct stat	buf;

	i = 0;
	tab = check_bin(token, shell);
	cmd = build_cmd(token);
	g_sig.pid = fork();
	if (g_sig.pid < 0)
		ft_putstr_fd("fail\n", 2);
	else if (!g_sig.pid)
	{
		while (tab && tab[i])
		{
			if (stat(tab[i], &buf) == 0)
				execve(tab[i], cmd, (*shell)->env);
			i++;
		}
		fd_write_errors(token);
		exit_prog(&token, NULL, -1);
	}
	end_exec(&cmd, &tab);
}
