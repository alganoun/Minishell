/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:42:59 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:49:35 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	**free_all(char **dest, int i)
{
	while (i > 0)
	{
		i--;
		free((void *)dest[i]);
	}
	free(dest);
	return (NULL);
}

size_t	count_split(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**malloc_dest(char **dest, char const *s, char c, size_t count)
{
	size_t	i;
	size_t	t_malloc;
	size_t	re_count;

	i = 0;
	re_count = 0;
	dest = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dest)
		return (0);
	while (s[i] && re_count < count)
	{
		while (s[i] == c && s[i])
			i++;
		t_malloc = 0;
		while (s[i] != c && s[i])
		{
			t_malloc++;
			i++;
		}
		dest[re_count] = (char *)malloc(sizeof(char) * (t_malloc + 1));
		if (!dest)
			return (free_all(dest, re_count));
		re_count++;
	}
	return (dest);
}

char	**split_split(char const *s, char c, char **dest, size_t count)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	x = 0;
	while (s[i] && x < count)
	{
		y = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			dest[x][y] = s[i];
			i++;
			y++;
		}
		dest[x][y] = '\0';
		x++;
	}
	dest[x] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	char		**dest;

	if (!s)
		return (NULL);
	dest = NULL;
	count = count_split(s, c);
	dest = malloc_dest(dest, s, c, count);
	dest[count] = 0;
	dest = split_split(s, c, dest, count);
	return (dest);
}
