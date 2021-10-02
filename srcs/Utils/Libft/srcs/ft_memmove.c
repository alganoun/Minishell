/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:43:39 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:47:18 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	d = dest;
	s = (char *)src;
	i = 0;
	if (d == s)
		return (dest);
	else if (d > s)
	{
		i = len - 1;
		while (len > 0)
		{
			d[i] = s[i];
			i--;
			len--;
		}
	}
	else
		dest = ft_memcpy(d, s, len);
	return (dest);
}
