/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:34:27 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/24 00:54:03 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *my_getenv(char *name, char **env)
{
	int i;

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
	int i;
	int j;
	char *str;

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
	int i;
	int j;
	char **tab;

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

int		value_existence(char *str, char **tab)
{
	int i;
	char *tmp;

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

int		count_to_copy(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += variable_len(&str[i]);
		else
			count++;
		i++;
	}
	return (count);
}

int		count_word(char *str, char *to_replace)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_strstr(&(str[i]), to_replace) == &(str[i]))
			{
				count++;
				i += ft_strlen(to_replace) - 1;
			}
		}
		i++;
	}
	return (count);
}

int		replace_word(char **str, char *name, char *value, char **tab)
{
	int i;
	int j;
	int count;
	char *result;

	i = 0;
	j = count_to_copy(*str);
	count = count_word(*str, name);
	result = ft_malloc(j + count * ft_strlen(value));
	j = 0;
	count = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
		{
			if (ft_strstr(&((*str)[i]), name) == &((*str)[i]))
			{
				ft_strcpy(&result[j], value);
				i += ft_strlen(name);
				j += ft_strlen(value);
				count = 1;
			}
			else if (value_existence(&((*str)[i]), tab) == 0)
				i += variable_len(&((*str)[i])) + 1;
		}
		result[j++] = (*str)[i++]; // il faut faire attention à la copie
	}
	result[j] = '\0';
	safe_free(str);
	*str = result;
	return (count);
}

void	get_variable_value(char **str, char **env)
{
	char **tab;
	int i;
	(void)str;
	tab = value_name_tab(env);
	i = 0;
	while(tab[i] != NULL)
	{
		replace_word(str, tab[i], my_getenv(tab[i] + 1, env), tab);
		i++;
	}
	free_tab(&tab);
}
