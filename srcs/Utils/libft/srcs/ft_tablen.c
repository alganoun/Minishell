/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 03:48:18 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 17:24:55 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}