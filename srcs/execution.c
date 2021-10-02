/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:39 by musoufi           #+#    #+#             */
/*   Updated: 2021/10/02 22:36:21 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_token *token, t_shell **shell)
{
	int			i;
	char		**tab;
	char		**cmd;
	struct stat	buf;

	i = 0;
	skip_bin(token);
	cmd = build_cmd(token);
	tab = bin(shell, cmd[0]);
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
	skip_bin(token);
	cmd = build_cmd(token);
	tab = bin(shell, cmd[0]);
	g_sig.pid = fork();
	if (g_sig.pid < 0)
		ft_putstr_fd("fail\n", 2);
	else if (!g_sig.pid)
	{
		while (tab[i])
		{
			if (stat(tab[i], &buf) == 0)
				execve(tab[i], cmd, (*shell)->env);
			i++;
		}
		fd_write_errors(token);
		exit_prog(&token, NULL, -1);
	}
	wait(&g_sig.pid);
	status_child();
}
