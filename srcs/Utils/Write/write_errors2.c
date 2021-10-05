/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:20:53 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/05 18:30:50 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	write_errors5(char *cmd, char *opt)
{
	ft_putstr_fd("Minishell :", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" :", STDERR_FILENO);
	write(STDERR_FILENO, opt, 2);
	ft_putendl_fd(" :invalid option", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage :", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
}
