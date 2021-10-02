/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:38:49 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:38 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		t_dest;

	t_dest = ft_strlen(dest);
	i = 0;
	if (size <= t_dest)
		return (size + ft_strlen(src));
	while (t_dest + i < (size - 1) && src[i] != '\0')
	{
		dest[i + t_dest] = src[i];
		i++;
	}
	dest[i + t_dest] = '\0';
	return (t_dest + ft_strlen(src));
}
