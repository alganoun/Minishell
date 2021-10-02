/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:45:14 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:57:56 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	x;

	x = 0;
	while (src[x] && x < n)
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	else if (start == 0 && len > ft_strlen(s))
		return (ft_strdup(s));
	else if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	else
	{
		if (len < ft_strlen(s + start))
			size = len + 1;
		else
			size = ft_strlen(s + start);
		str = malloc(sizeof(char) * size);
		if (!str)
			return (NULL);
		str = ft_strncpy(str, (char *)(s + start), len);
	}
	return (str);
}
