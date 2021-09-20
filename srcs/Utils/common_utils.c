/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:00:40 by alganoun          #+#    #+#             */
/*   Updated: 2021/09/20 17:02:29 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		space_into_dot(char **str, char **env)
{
	int i;

	i = 0;
	if (add_missing_space(str) == -1)
		return (-1);
	if (*str == NULL)
		return (write_errors(REDIR_ERROR, NULL));
	while ((*str)[i])
	{
		if ((*str)[i] == '~')
			tild_replacer(str, env);
		if (((*str)[i] == '"' && i == 0)
			|| ((*str)[i] == '"' && (*str)[i - 1] != '\\'))
			i = double_quote(*str, i);
		else if (((*str)[i] == '\'' && i == 0)
			|| ((*str)[i] == '\'' && (*str)[i - 1] != '\\'))
			i = simple_quote(*str, i) ;
		else if ((*str)[i] == ';') // il faut changer la detection du '/'
			return (write_errors(BAD_CHAR, NULL));
		else if ((*str)[i] == ' ')
			(*str)[i] = 13;
		i++;
	}
	return (0);
}

int		variable_len(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] && (str[i] < 32 || str[i] > 47)
				&& (str[i] < 58 || str[i] > 64) )
			{
				count++;
				i++;
			}
			return (count);
		}
		i++;
	}
	return (count);
}

int		is_redir(char *str)
{
	int i = 0;
	while (str[i] > 47 && str[i] < 58)
		i++;
	if ((str[i] == '>' && str[i + 1] == '\0')
			|| (str[i] == '<' && str[i + 1] == '\0')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0'))
		return (1);
	return (0);
}

int		variable_existence(char *str, char **tab)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (str && str[0] == '$')
		str++;
	while (str && tab && tab[i] != NULL)
	{
		while (str[count] != '=')
			count++;
		if (ft_strncmp(str, tab[i], count) == 0)
			return (i);
		i++;
	}
	return (0);
}

int		reallocate_tab(char ***tab, char *str)
{
	char **tmp;
	int i;
	tmp = (char **)ft_malloc(sizeof(char *) * (tablen(*tab) + 2));
	if (!tmp)
		return (-1);
	i = 0;
	while ((*tab)[i] != NULL)
	{
		tmp[i] = (*tab)[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	free(*tab);
	*tab = tmp;
	return (0);
}


