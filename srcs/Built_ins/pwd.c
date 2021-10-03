/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 23:29:18 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/03 12:11:59 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_process(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
	{
		ft_putendl_fd(buff, 1);
		g_sig.exit_status = 0;
	}
	else /*too many argyuments, bad option, ...*/
	{
		ft_putendl_fd("PATH error", STDERR_FILENO);
		g_sig.exit_status = 1;
	}
	return (TRUE);
}
