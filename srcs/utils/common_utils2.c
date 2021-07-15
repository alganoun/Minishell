/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:55:03 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/15 21:21:46 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		space_into_dot(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"') // il faut regler le soucis des guillemets pour les arguments
		{
			i++;
			while ((*str)[i] && (*str)[i] != '"')
			{
				if ((*str)[i] == '\\' && (*str)[i + 1] == '"')
					i++;
				i++;
			}
			if ((*str)[i] == '\0')
				return (write_errors(3, *str));
		}
		else if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
			{
				if ((*str)[i] == '\\' && (*str)[i + 1] == '\'')
					i++;
				i++;
			}
			if ((*str)[i] == '\0')
				return (write_errors(3, *str));
		}
		else if ((*str)[i] == ' ')
			(*str)[i] = '.';
		i++;
	}
	return (0);
}

void	quote_remover2(char **str, int len)
{
	char *tmp;
	int i;
	int j;

	tmp = malloc(len + 1);
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
