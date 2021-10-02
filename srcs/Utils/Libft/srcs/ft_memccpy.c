/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:15:27 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:47:09 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*sdest;
	unsigned char	*ssrc;

	sdest = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		sdest[i] = ssrc[i];
		if (ssrc[i] == (unsigned char)c)
			return ((void *)sdest + i + 1);
		i++;
	}
	return (NULL);
}
