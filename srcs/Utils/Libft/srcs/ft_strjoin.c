/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:37:49 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 16:08:07 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	x;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	x = 0;
	if (s1)
		while (s1[++i])
			str[x++] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			str[x++] = s2[i];
	str[x] = '\0';
	return (str);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	x;

	str = (char *)malloc(sizeof(char) *(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	x = 0;
	if (s1)
		while (s1[++i])
			str[x++] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			str[x++] = s2[i];
	str[x] = '\0';
	free(s1);
	return (str);
}

char	*strjoin_free_s2_add_n(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	x;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	x = 0;
	if (s1)
		while (s1[++i])
			str[x++] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			str[x++] = s2[i];
	str[x++] = '\n';
	str[x] = '\0';
	free(s1);
	free(s2);
	return (str);
}
