/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:55:03 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/09 09:54:43 by allanganoun      ###   ########.fr       */
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

int		space_into_dot(char **str)
{
	int i;

	i = 0;
	if (add_missing_space(str) == -1)
		return (-1);
	if (*str == NULL)
		return (write_errors(REDIR_ERROR, NULL));
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
			i = double_quote(*str, i);
		else if ((*str)[i] == '\'')
			i = simple_quote(*str, i) ;
		else if ((*str)[i] == ';' || (*str)[i] == '\\')
			return (write_errors(BAD_CHAR, NULL));
		else if ((*str)[i] == ' ')
			(*str)[i] = 13;
		i++;
	}
	return (0);
}

void	quote_remover2(char **str, int len)
{
	char *tmp;
	int i;
	int j;

	tmp = ft_malloc(len + 1);
	i = 0;
	j = 0;
	while ((*str)[i] && (*str)[0] == '"')
	{
		if (((*str)[i] != '"' && (*str)[i] != '\\')
			|| ((*str)[i] == '\\' && (*str)[i + 1] != '"')
			|| ((*str)[i] == '"' && (*str)[i - 1] == '\\'))
			tmp[j++] = (*str)[i];
		i++;
	}
	while ((*str)[i] && (*str)[0] == '\'')
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

void	quote_remover(char **str)
{
	int len;
	int	i;

	i = 0;
	len = 0;
	if (*str)
	{
		while ((*str)[i] && (*str)[0] == '"')
		{
			if ((*str)[i] != '"')
				len++;
			i++;
		}
		while ((*str)[i] && (*str)[0] == '\'')
		{
			if ((*str)[i] != '\'')
				len++;
			i++;
		}
		if (len > 0)
			quote_remover2(str, len);
	}
}

