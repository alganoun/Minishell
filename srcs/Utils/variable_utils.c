/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:34:27 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 20:09:44 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_convertible(char *str, int index)
{
	int	begin;
	int	end;
	int	i;

	begin = -1;
	end = -1;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && i == 0)
			|| (str[i] == '"' && str[i - 1] != '\\'))
			i = double_quote(str, i);
		if (((str[i] == '\'' && i == 0) || (str[i] == '\''
					&& str[i - 1] != '\\')) && begin == -1)
			begin = i;
		else if (str[i] == '\'' && begin != -1)
		{
			end = i;
			if (index > begin && index < end)
				return (FALSE);
			begin = 0;
		}
		i++;
	}
	return (SUCCESS);
}

int	count_to_copy(char *str, char *to_replace)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && ft_strstr(&(str[i]), to_replace) == &(str[i]))
			i += variable_len(&str[i]);
		else
			count++;
		i++;
	}
	return (count);
}

int	count_word(char *str, char *to_replace)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
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

int	replace_word(char **str, char *name, char *value, char **tab)
{
	int		i;
	int		j;
	int		ret;
	char	*result;

	i = 0;
	j = 0;
	ret = 0;
	result = malloc(count_to_copy(*str, name)
			+ (count_word(*str, name) * ft_strlen(value)) + 1);
	while (str && (*str)[i] != '\0')
	{
		if ((*str)[i] == '$' && is_convertible(*str, i) == SUCCESS)
		{
			if (ft_strstr(&((*str)[i]), name) == &((*str)[i]))
			{
				ft_strcpy(&result[j], value); // reduire ici aussi
				i += ft_strlen(name);
				j += ft_strlen(value);
				ret = 1;
			}
			else if (value_existence(&((*str)[i]), tab) == 0)
				i += variable_len(&((*str)[i]));
		}
		if ((*str)[i] != '\0')
			result[j++] = (*str)[i++];
	}
	result[j] = '\0';
	free_replace(str, &result);
	return (ret);
}

void	get_variable_value(char **str, char **env)
{
	char	**tab;
	char	**env2;
	char	*sig_int;
	int		i;

	sig_int = ft_itoa(g_sig.sigquit);
	env2 = ft_tabdup(env);
	reallocate_tab(&env2, ft_strjoin("?=", sig_int));
	tab = value_name_tab(env2);
	i = 0;
	while (tab[i] != NULL && *str)
	{
		if (replace_word(str, tab[i], my_getenv(tab[i] + 1, env2), tab) == 1)
			i = -1;
		i++;
	}
	safe_free(&sig_int);
	free_tab(&tab);
	free_tab(&env2);
}
