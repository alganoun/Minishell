/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:39:03 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:57:26 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	in_dico(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	a;
	size_t	z;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	a = 0;
	z = ft_strlen(s1);
	while (s1[a] && in_dico(s1[a], set))
		a++;
	while (z > a && in_dico(s1[z - 1], set))
		z--;
	str = (char *)malloc(sizeof(char) * (z - a + 1));
	if (!str)
		return (NULL);
	while (a < z)
		str[i++] = s1[a++];
	str[i] = '\0';
	return (str);
}
