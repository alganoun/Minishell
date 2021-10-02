/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:36:49 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:56:53 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	size_s2;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	if (n == 0)
		return (NULL);
	size_s2 = ft_strlen(s2);
	while (s1[i] && i <= (n - size_s2))
	{
		if (ft_strncmp(&s1[i], s2, size_s2) == 0)
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
