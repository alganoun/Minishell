/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 22:11:43 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/03 11:53:13 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	simple_quote(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int	double_quote(char *str, int i)
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

int	is_printable_quote(char *str, int i, char c)
{
	if ((str[i] != c && str[i] != '\\')
		|| (str[i] == '\\' && str[i + 1] != c)
		|| (str[i] == c && str[i - 1] == '\\'))
		return (SUCCESS);
	return (FALSE);
}

void	printable_quote_cpy(char *str, char **tmp, int *i, int *j)
{
	int	quit;

	quit = 0;
	(*i)++;
	while (str[*i] && quit == 0)
	{
		if (str[*i] == '"' && str[(*i) - 1] != '\\')
			quit = 1;
		else if (is_printable_quote(str, *i, '"') == SUCCESS)
			(*tmp)[(*j)++] = str[*i];
		if (quit == 0)
			(*i)++;
	}
}

void	printable_quote_cpy2(char *str, char **tmp, int *i, int *j)
{
	int	quit;

	quit = 0;
	(*i)++;
	while (str[*i] && quit == 0)
	{
		if (str[*i] == '\'')
			quit = 1;
		else
			(*tmp)[(*j)++] = str[*i];
		if (quit == 0)
			(*i)++;
	}
}
