/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:05:17 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/01 18:12:49 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	equal_detection(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	count_to_keep(char *str, char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], equal_detection(env[i])) != 0)
			count++;
		i++;
	}
	return (count);
}

int	unset_is_forbiden_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			if (str[i] == '_' || (str[i] == '$' && str[i + 1] == '?')
				|| ft_isdigit(str[i]))
				g_sig.exit_status = 0;
			else
				g_sig.exit_status = 1;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
