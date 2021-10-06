/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:20:53 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 14:32:38 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	write_errors5(char *cmd, char *opt, int name)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	write(STDERR_FILENO, opt, 2);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage : ", STDERR_FILENO);
	if (name == 0)
		ft_putendl_fd(cmd, STDERR_FILENO);
	else if (name == 1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(" [name ...]", STDERR_FILENO);
	}
	else if (name == 2)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(" [dir]", STDERR_FILENO);
	}
	g_sig.exit_status = 2;
	return (-1);
}
