/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:15:55 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/03 11:53:23 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_to_copy(char *str, char *to_replace)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && ft_strstr(&(str[i]), to_replace) == &(str[i]))
			i += variable_len(&str[i]);
		else
			count++;
		i++;
	}
	return (count);
}

int	count_word(char *str, char *to_replace)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			if (ft_strstr(&(str[i]), to_replace) == &(str[i]))
			{
				count++;
				i += ft_strlen(to_replace) - 1;
			}
		}
		i++;
	}
	return (count);
}
