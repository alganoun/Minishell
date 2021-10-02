/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:06:24 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/02 22:49:46 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_process(t_token *token, char **env)
{
	int	i;

	i = 0;
	if (token->arg)
	{
		ft_putstr_fd(token->cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(token->arg[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_sig.exit_status = 127;
	}
	else
	{
		while (env[i] != NULL)
		{
			if (ft_strchr(env[i], '=') != NULL)
			{
				ft_putstr_fd(env[i], 1);
				ft_putchar_fd('\n', 1);
			}
			i++;
		}
		g_sig.exit_status = 0;
	}
	return (TRUE);
}
