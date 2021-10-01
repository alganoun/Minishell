/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:38:22 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 15:44:57 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_itoa_lol(int nb, char **str, char *base, int i)
{
	long	nbr;
	int		t_base;

	nbr = nb;
	t_base = 10;
	if (nbr < 0)
	{
		str[0][i] = '-';
		i++;
		nbr *= -1;
	}
	str[0][i] = base[nbr % t_base];
	str[0][i + 1] = '\0';
	if ((nbr / t_base) > 0)
		ft_itoa_lol((nbr / t_base), str, base, i + 1);
}

char	*ft_rev(char *str, int size)
{
	int		i;
	int		x;
	int		temp;

	x = size - 1;
	i = 0;
	if (str[0] == '-')
		i++;
	while (i < x)
	{
		temp = str[i];
		str[i] = str[x];
		str[x] = temp;
		i++;
		x--;
	}
	return (str);
}

int	count_tnum(int nbr)
{
	int		size;
	long	nb;

	nb = nbr;
	size = 1;
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb >= 10)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*str;
	char	*base;
	int		t_str;
	int		t_malloc;

	base = "0123456789";
	t_malloc = count_tnum(nb);
	str = (char *)malloc(sizeof(char) * (t_malloc + 1));
	if (!str)
		return (0);
	ft_itoa_lol(nb, &str, base, 0);
	t_str = ft_strlen(str);
	str = ft_rev(str, t_str);
	return (str);
}
