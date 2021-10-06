/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:06:24 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 03:04:49 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_errors_env(char *cmd, char *opt)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(" : illegal option -- ", STDERR_FILENO);
	write(STDERR_FILENO, &opt[1], 1);
	ft_putstr_fd("\nusage : ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	g_sig.exit_status = 1;
	return (-1);
}

int	env_process(t_token *token, char **env)
{
	int	i;

	i = 0;
	if (token->option)
		return (write_errors_env(token->cmd, token->option[0]));
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
				ft_putendl_fd(env[i], 1);
			i++;
		}
		g_sig.exit_status = 0;
	}
	return (TRUE);
}
