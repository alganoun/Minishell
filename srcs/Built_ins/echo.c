/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:42:11 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/02 22:17:48 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_write(t_token *token, char *str, int i)
{
	write (1, str, ft_strlen(str));
	if (token->arg[i + 1] != NULL)
		write (1, " ", 1);
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
