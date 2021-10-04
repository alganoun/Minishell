/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:42:11 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/04 04:32:52 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_write(t_token *token, char *str, int i)
{
	if (i != 0 && ft_strlen(token->arg[i]) > 0)
		ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
}

int	echo_process(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	while (token->arg && token->arg[i] != NULL)
	{
		str = ft_strdup(token->arg[i]);
		echo_write(token, str, i);
		safe_free(&str);
		i++;
	}
	i = 0;
	if (token->option)
	{
		while (is_echo_option(token->option[i]) == -1)
			i++;
		if (token->option[i] == NULL)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	g_sig.exit_status = 0;
	return (TRUE);
}
