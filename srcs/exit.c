/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:22:24 by musoufi           #+#    #+#             */
/*   Updated: 2021/09/22 00:19:09 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
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
	if (status > 0)
		g_sig.sigquit = status;
	if (token)
		free_struct(token);
	if (exit_message)
		ft_putendl_fd(exit_message, STDERR_FILENO);
	rl_clear_history();
	exit(status);
}

char**	quote_remover_exit(t_token *token)
{
	if (token->arg)
		return (token->arg);
	else if (token->option)
		return (token->option);
	return (NULL);
}

long	*ft_atols(const char *str, long *dst)
{
	int i;
	int signcheck;
	__int128_t nb;

	i = 0;
	nb = 0;
	signcheck = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		signcheck = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nb > LONG_MAX || nb < LONG_MIN)
		return (NULL);
	*dst = nb * signcheck;
	return (dst);
}


void	exit_cmd(t_token *token)
{
	char **arg;
	void *status;
	long nb;

	if (token->arg || token->option)
	{
		arg = quote_remover_exit(token);
		if (token->arg == NULL && token->option)
			status = ft_atols(token->option[0], &nb);
		else
			status = ft_atols(token->arg[0], &nb);
		if ((token->arg && token->option) || (arg[0] && arg[1]))
		{
			ft_putendl_fd("exit\nminishell: exit: too many arguments", STDERR_FILENO);
			exit_prog(&token, "exit", 1);
		}
		else if ((arg[0] && ft_strisnum(arg[0]) == 0) || (status == NULL))
		{
			ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg[0], STDERR_FILENO);
			exit_prog(&token, ": numeric argument required", 255);
		}
		else if (arg[0] && ft_strisnum(arg[0]) != 0)
			exit_prog(&token, "exit", nb);
	}
	else
		exit_prog(&token, "exit", 0);
}
