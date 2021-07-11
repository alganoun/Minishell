/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:00:40 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/11 19:33:23 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		 tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int		display_txt(char *str)
{
	int fd;
	int ret;
	char *line;
	ret = 1;

	fd = open(str, O_RDONLY);
	printf("%d\n", fd);
	if (fd > 0)
	{
		while(ret > 0)
		{
			ret = get_next_line(fd, &line);
			write_output(line);
			free(line);
		}
		ret = get_next_line(fd, &line);
		write_output(line);
		free(line);
	}
	if (ret != 0)
		return (write_errors(1, str));
	return (0);
}

int		reallocate_tab(char ***tab, char *str)
{
	char **tmp;
	int i;
	tmp = (char **)malloc(sizeof(char *) * (tablen(*tab) + 2));
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

int		space_into_dot(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			i++;
			while (((*str)[i] && (*str)[i] != '"')
				&& ((*str)[i] && (*str)[i] != '\''))
				i++;
			if ((*str)[i] == '\0')
				return (write_errors(3, *str));
		}
		else if ((*str)[i] == ' ')
			(*str)[i] = '.';
		i++;
	}
	return (0);
}

void	quote_remover(char **str)
{
	int len;
	int	i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	len = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != '"' && (*str)[i] != '\'')
			len++;
		i++;
	}
	tmp = malloc(len + 1);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != '"' && (*str)[i] != '\'')
			tmp[j++] = (*str)[i];
		i++;
	}
	tmp[j] = '\0';
	safe_free(str);
	*str = tmp;
}
