/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:26:03 by sbaranes          #+#    #+#             */
/*   Updated: 2021/10/01 17:07:10 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	skip_space_t(char *str, size_t *i)
{
	while (str[*i] == ' ')
	{
		*i += 1;
	}
}

int	skip_space_i(char *str, int char_index)
{
	int	i;

	i = char_index;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	check_space_end(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] != ' ')
			return (1);
		*i += 1;
	}
	return (0);
}

float	ft_abs(float a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}
