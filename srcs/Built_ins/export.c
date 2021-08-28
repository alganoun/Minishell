/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:34:34 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/29 00:13:35 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && (i > 0))
			return (i);
		i++;
	}
	return (0);
}

int		is_exportable(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=' && ft_isalnum(str[i]) == 1)
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		i++;
	}
	if (str[i] != '=' && str[i] != '\0')
		return (FALSE);
	return (SUCCESS);
}

char	**export_name_tab(char **env)
{
	int i;
	int j;
	char **tab;

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

void	export_process2(t_token *token, char ***env, char **str, char **tab)
{
	if (variable_existence(*str, tab) > 0 && check_name(*str) > 0)
	{
		free((*env)[variable_existence(*str, tab)]);
		(*env)[variable_existence(*str, tab)] = ft_strdup(*str);
	}
	else if (is_exportable(*str) == 0)
		write_errors(6, &((*str)[check_name(*str)]));
	else
	{
		if (token->exp == 1)
			get_variable_value(str, *env);
		reallocate_tab(env, *str);
	}
}

int		export_process(t_token *token, char ***env)
{
	int i;
	char *str;
	char **tab;

	i = 0;
	tab = export_name_tab(*env);
	if (token->arg == NULL || token->arg[0][0] == '\0')
			print_sorted_tab(*env);
	else
	{
		while (token->arg && token->arg[i] != NULL)
		{
			str = ft_strdup(token->arg[i]);
			export_process2(token, env, &str, tab);
			i++;
		}
	}
	free_tab(&tab);
	return (TRUE);
}
