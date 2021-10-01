/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:07:55 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 19:00:10 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_export_format(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_malloc(ft_strlen(str) + 3);
	while (str[i])
	{
		if (i != 0 && str[i - 1] == '=')
			new_str[j++] = '"';
		new_str[j++] = str[i++];
		if (str[i] == '\0' && ft_strchr(str, '=') != NULL)
			new_str[j++] = '"';
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*sort_tab_export(char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	while (tab[j] != NULL)
	{
		k = 0;
		while (tab[i][k] == tab[j][k])
			k++;
		if (tab[i][k] > tab[j][k])
		{
			i++;
			j = i + 1;
		}
		else if (tab[i][k] < tab[j][k])
			j++;
	}
	return (tab[i]);
}

void	reallocate_unsorted_tab(char ***tab, char *str)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = malloc(sizeof(char *) * tablen(*tab));
	while ((*tab)[i] != NULL)
	{
		if (ft_strcmp((*tab)[i], str) == 0)
			i++;
		else
			new_tab[j++] = ft_strdup((*tab)[i++]);
	}
	new_tab[j] = NULL;
	free(*tab);
	*tab = new_tab;
}

void	print_sorted_tab(char **tab)
{
	int		i;
	int		tab_len;
	char	**tab2;
	char	**tmp;

	i = 0;
	tab_len = tablen(tab);
	tab2 = ft_tabdup(tab);
	tmp = malloc(sizeof(char *) * (tab_len + 1));
	while (tab_len > 0)
	{
		tmp[i] = ft_strjoin("declare -x ",
				str_export_format(sort_tab_export(tab2)));
		reallocate_unsorted_tab(&tab2, sort_tab_export(tab2));
		i++;
		tab_len--;
	}
	tmp[i] = NULL;
	i = 0;
	while (tmp[i] != NULL)
		write_output(tmp[i++]);
	free_tab(&tab2);
	free_tab(&tmp);
}
