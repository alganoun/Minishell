/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:46:26 by musoufi           #+#    #+#             */
/*   Updated: 2021/10/03 12:32:01 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	redisplay(void)
{
	if (g_sig.cmd != 1)
		ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_sig.cmd != 1)
		rl_redisplay();
	g_sig.exit_status = 1;
}

void	sigint(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_sig.pid != 0)
	{
		if (!kill(g_sig.pid, sig))
		{
			if (sig == SIGQUIT)
			{
				ft_putstr_fd("Quit: 3\n", 1);
				g_sig.exit_status = 131;
			}
			else if (sig == SIGINT)
			{
				ft_putchar_fd('\n', 1);
				g_sig.exit_status = 130;
			}
		}
	}
	if (sig == SIGINT)
		redisplay();
}

char	**strenv(char *s, char **env)
{
	char	**dst;

	dst = ft_split(my_getenv(s, env) + ft_strlen(s), ':');
	return (dst);
}
