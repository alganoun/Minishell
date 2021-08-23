/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:46:26 by musoufi           #+#    #+#             */
/*   Updated: 2021/08/20 16:11:03 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 1;
	}
}

char	**strenv(char *s, char **env)
{
	char	**dst;

	dst = ft_split(my_getenv(s, env) + ft_strlen(s), ':');
	return (dst);
}
