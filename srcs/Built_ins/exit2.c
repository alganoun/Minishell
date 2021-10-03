/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:41:53 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/03 11:53:51 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (g_sig.exit_status != -1)
		status = g_sig.exit_status;
	if (status != -1)
		g_sig.sigquit = status;
	if (token)
		free_struct(token);
	if (exit_message)
		ft_putendl_fd(exit_message, STDERR_FILENO);
	rl_clear_history();
	exit(status);
}

char	**quote_remover_exit(t_token *token)
{
	if (token->arg)
		return (token->arg);
	else if (token->option)
		return (token->option);
	return (NULL);
}

long	*ft_atols(const char *str, long *dst)
{
	int			i;
	int			signcheck;
	__int128_t	nb;

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
