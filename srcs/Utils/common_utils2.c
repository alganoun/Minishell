/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:55:03 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/23 20:45:53 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		simple_quote(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '\'')
	{
		if (str[i] == '\\' && str[i + 1] == '\'')
			i++;
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int		double_quote(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '\\' && str[i + 1] == '"')
			i++;
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int		quote_remover_cpy(char *str, int option)
{
	int i;
	int len;

	len = 0;
	if (option == 1)
	{
		i = 0;
		while (str && str[i])
			if (str[i++] != '"')
				len++;
	}
	else if (option == 2)
	{
		i = 0;
		while (str && str[i])
			if (str[i++] != '\'')
				len++;
	}
	return (len);
}


void	quote_remover2(char **str, int len, int option)
{
	char *tmp;
	int i;
	int j;

	tmp = ft_malloc(len + 1);
	i = 0;
	j = 0;
	while ((*str)[i] && option == 1)
	{
		if (((*str)[i] != '"' && (*str)[i] != '\\')
			|| ((*str)[i] == '\\' && (*str)[i + 1] != '"')
			|| ((*str)[i] == '"' && (*str)[i - 1] == '\\'))
			tmp[j++] = (*str)[i];
		i++;
	}
	while ((*str)[i] && option == 2)
	{
		if (((*str)[i] != '\'' && (*str)[i] != '\\')
			|| ((*str)[i] == '\\' && (*str)[i + 1] != '\'')
			|| ((*str)[i] == '\'' && (*str)[i - 1] == '\\'))
			tmp[j++] = (*str)[i];
		i++;
	}
	tmp[j] = '\0';
	safe_free(str);
	*str = tmp;
}

void	quote_remover(char **str, t_token **token)
{
	int found;
	int	i;

	i = 0;
	found = 0;
	while (*str && (*str)[i] && found == 0)
	{
		if ((*str)[i] == '"')
			found = 1;
		else if ((*str)[i] == '\'')
			found = 2;
		i++;
	}
	if (found == 1 || found == 0)
		(*token)->exp = 0;
	else if (found == 2)
		(*token)->exp = 1;
	if (*str && found > 0)
		quote_remover2(str, quote_remover_cpy(*str, found), found);
}

