/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:39:32 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/03 00:14:32 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && i > 0)
			return (i);
		i++;
	}
	return (0);
}

int	is_exportable(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (FALSE);
	while (str[i] && str[i] != '=' && ft_isalnum(str[i]) == 1)
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		i++;
	}
	if ((str[i] != '=' && str[i] != '\0')
		|| (str[i] == '=' && str[i + 1] == '\0'))
		return (FALSE);
	return (SUCCESS);
}

char	**export_name_tab(char **env)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	tab = ft_malloc(sizeof(char *) * (tablen(env) + 1));
	while (env[i] != NULL)
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = NULL;
	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '=')
			j++;
		tab[i][j + 1] = '\0';
		i++;
	}
	return (tab);
}

int	is_forbiden_name2(char *str, int i, int only_assign)
{
	while (i != 0 && str[i])
	{
		if (str[i] == '=' && only_assign > 0)
			i--;
		else if (!ft_isalpha(str[i]))
		{
			if (str[i] == '_' || str[i] == '?' || str[i] == '\\')
				g_sig.exit_status = 0;
			else
				g_sig.exit_status = 1;
			return (TRUE);
		}
		i--;
	}
	return (FALSE);
}

int	is_forbiden_name(char *str)
{
	int		i;
	char	*end;
	int		only_assign;

	i = 0;
	only_assign = 0;
	end = ft_strrchr(str, '=');
	if (end == NULL)
		return (FALSE);
	if (str[i] == '=' && !str[i + 1])
	{
		g_sig.exit_status = 1;
		return (TRUE);
	}
	while (&str[i] != end)
	{
		if (str[i] == '=' && only_assign == i)
			only_assign = 0;
		else
			only_assign++;
		i++;
	}
	i--;
	return (is_forbiden_name2(str, i, only_assign));
}
