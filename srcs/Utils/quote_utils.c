/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:55:03 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/29 10:29:34 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		quote_remover_cpy(char *str, int *len, char c, int *i)
{
	int quit;

	quit = 0;
	(*i)++;
	while (str[*i] && quit == 0)
	{
		if (str[*i] == c)
			quit = 1;
		//else if (c == '\'' && str[*i] == '\\' && str[(*i) + 1] == c)
		//	return (write_errors(1, NULL));
		else if (str[(*i)++] != c)
			(*len)++;
	}
	return (SUCCESS);
}

void	quote_remover2(char **str, int len)
{
	char *tmp;
	int i;
	int j;

	tmp = ft_malloc(len + 1);
	i = 0;
	j = 0;
	//(*str)[ft_strlen(*str) + 1] = '\0';
	while ((*str)[i] != '\0')
	{
		if (((*str)[i] == '"' && i == 0)
			|| ((*str)[i] == '"' && (*str)[i - 1] != '\\'))
			printable_quote_cpy(*str, &tmp, &i, &j);
		else if (((*str)[i] == '\'' && i == 0)
			|| ((*str)[i] == '\'' && (*str)[i - 1] != '\\'))
			printable_quote_cpy2(*str, &tmp, &i, &j);
		else if ((*str)[i] && (*str)[i] == '\\' && (*str)[i - 1] == '\\')
			tmp[j++] = (*str)[i++];
		else if ((*str)[i] && (*str)[i] != '\\')
			tmp[j++] = (*str)[i];
		i++;
	}
	tmp[j] = '\0';
	safe_free(str);
	*str = tmp;
}

int		quote_remover(char **str)
{
	int len;
	int	i;

	i = 0;
	len = 0;

	while (*str && (*str)[i])
	{
		if (((*str)[i] == '"' && i == 0)
			|| ((*str)[i] == '"' && (*str)[i - 1] != '\\'))
			quote_remover_cpy(*str, &len, '"', &i);
		else if (((*str)[i] == '\'' && i == 0)
			|| ((*str)[i] == '\'' && (*str)[i - 1] != '\\'))
		{
			if (quote_remover_cpy(*str, &len, '\'', &i) == -1)
				return (-1);
		}
		else if ((*str)[i] != '\\')
			len++;
		i++;
	}
	quote_remover2(str, len);
	return (SUCCESS);
}
