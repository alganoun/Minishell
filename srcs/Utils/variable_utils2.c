/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 02:13:06 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 20:10:38 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*my_getenv(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(name, env[i], ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

void	add_dollar(char ***tab)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while ((*tab)[i] != NULL)
	{
		j = 1;
		str = ft_malloc(ft_strlen((*tab)[i]) + 2);
		str[0] = '$';
		while ((*tab)[i][j - 1])
		{
			str[j] = (*tab)[i][j - 1];
			j++;
		}
		str[j] = '\0';
		free ((*tab)[i]);
		(*tab)[i] = str;
		str = NULL;
		i++;
	}
}

char	**value_name_tab(char **env)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	tab = ft_tabdup(env);
	while (tab && tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] && tab[i][j] != '=')
			j++;
		tab[i][j] = '\0';
		i++;
	}
	add_dollar(&tab);
	return (tab);
}

int	value_existence(char *str, char **tab)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(str);
	i = variable_len(tmp) + 1;
	if (i == 1)
		return (1);
	tmp[i] = '\0';
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strcmp(tmp, tab[i]) == 0)
		{
			safe_free(&tmp);
			return (i);
		}
		i++;
	}
	safe_free(&tmp);
	return (0);
}
