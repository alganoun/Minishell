/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:22:24 by musoufi           #+#    #+#             */
/*   Updated: 2021/08/19 12:59:01 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_prog(t_token **token, char *exit_message, int status)
{
	if (token)
		free_struct(token);
	if (exit_message)
		ft_putendl_fd(exit_message, STDERR_FILENO);
	exit(status);
}

void	exit_cmd(t_token *token)
{
	if (token->arg)
	{
		if (token->arg[0] && token->arg[1])
			exit_prog(&token, "minishell: exit: too many arguments", 1);
		else if (token->arg[0] && ft_strisnum(token->arg[0]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(token->arg[0], STDERR_FILENO);
			exit_prog(&token, ": numeric argument required", 255);
		}
		else if (token->arg[0] && ft_strisnum(token->arg[0]) != 0)
			exit_prog(&token, "exit", ft_atoi(token->arg[0]));
	}
	else
		exit_prog(&token, "exit", 0);
}
