/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 23:29:18 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 17:48:06 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_process(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
		ft_putendl_fd(buff, 1);
	else
		write_errors(PATH_ERROR, NULL);
	return (TRUE);
}
