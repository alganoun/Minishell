/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/22 19:59:06 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		get_next_line(int fd, char **line)
{
	int		i;
	int		l;
	int		r;
	char 	c;
	char	*tmp;

	l = 1;
	r = 0;
	if(!(*line = malloc(1)))
		return (-1);
	(*line)[0] = 0;
	while ((r = read(fd, &c, 1)) && l++ && c != '\n')
	{
		if(!(tmp = malloc(l)))
		{
			free(*line);
			return (0);
		}
		i = -1;
		while (++i < l - 2)
			tmp[i] = (*line)[i];
		tmp[i] = c;
		tmp[i + 1] = '\0';
		free(*line);
		*line = tmp;
	}
	return (r);
}

void		prompt(void)
{
	char	*tmp;
	size_t	len;
	size_t	slash;

	tmp = getenv("USER");
	ft_putstr_fd("\033[32;1m", 1);
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("@\033[0m:", 1);
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	slash = 0;
	while (--len && slash < 3)
		if (tmp[len] == '/')
			slash++;
	ft_putstr_fd("\e[1;34m", 1);
	while (tmp[++len])
		ft_putchar_fd(tmp[len], 1);
	ft_putstr_fd("$\e[0m ", 1);
	free(tmp);
}

void	get_next_input(char **line)
{
	if (*line != NULL)
	{
		safe_free(line);
		*line = NULL;
	}
	prompt();
	*line = readline("");
	add_history(*line);
}
