/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:47 by musoufi           #+#    #+#             */
/*   Updated: 2021/08/19 12:59:39 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pip(int *a, int *b, int *c, int close_all)
{
	if (close_all == TRUE)
	{
		close(*a);
		close(*b);
		close(*c);
	}
	else
	{
		close(*a);
		dup(*b);
		close(*c);
	}
}

void	child(t_token *token, t_shell **shell, int fd[2], int *fdd)
{
	int	out;
	int	in;

	out = 1;
	in = 0;
	close(fd[0]);
	pip(&in, fdd, fdd, FALSE);
	if (token->next && strncmp(token->next->operator, "|", 2) == 0)
		pip(&out, &fd[1], &fd[1], FALSE);
	choose(token, shell, TRUE);
}

int	fork_process(t_token *token, t_shell **shell, int fdd)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	g_sig.pid = fork();
	if (g_sig.pid < 0)
	{
		pip(&fd[0], &fd[1], &fdd, TRUE);
		return (-1);
	}
	else if (!g_sig.pid)
		child(token, shell, fd, &fdd);
	wait(&g_sig.pid);
	pip(&fdd, &fdd, &fd[1], TRUE);
	return (fd[0]);
}
