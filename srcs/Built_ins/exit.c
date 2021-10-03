/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:22:24 by musoufi           #+#    #+#             */
/*   Updated: 2021/10/03 12:08:08 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_cmd2(t_token *token, char **arg, long nb)
{
	if ((token->arg && token->option) || (arg[0] && arg[1]))
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments",
			STDERR_FILENO);
		exit_prog(&token, "exit", 1);
	}
	else if (arg[0] && ft_strisnum(arg[0]) != 0)
		exit_prog(&token, "exit", nb);
}

void	exit_cmd(t_token *token)
{
	char	**arg;
	void	*status;
	long	nb;

	if (token->arg || token->option)
	{
		arg = quote_remover_exit(token);
		if (token->arg == NULL && token->option)
			status = ft_atols(token->option[0], &nb);
		else
			status = ft_atols(token->arg[0], &nb);
		if ((arg[0] && ft_strisnum(arg[0]) == 0) || (status == NULL))
		{
			ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg[0], STDERR_FILENO);
			exit_prog(&token, ": numeric argument required", 255);
		}
		else
			exit_cmd2(token, arg, nb);
	}
	else
		exit_prog(&token, "exit", 0);
}
