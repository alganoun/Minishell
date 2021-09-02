/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/09/02 11:43:24 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		display_txt(char *str)
{
	int fd;
	int ret;
	char *line;
	ret = 1;

	fd = open(str, O_RDONLY);
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

char *prompt(char **env)
{
	char *tmp;
	char *line;
	size_t len;

	line = ft_strjoin("[", my_getenv("USER", env));
	line = ft_strjoin(line, "]");
	tmp = getcwd(NULL, 0);
	if (ft_strcmp(tmp, ft_strjoin("/Users/", my_getenv("USER", env))) == 0) // il faut faire gaffe à utiliser notre env et pas celui du zsh
		tmp = "~";
	else
	{
		len = ft_strlen(tmp);
		while (tmp[len] != '/')
			len--;
		tmp = &tmp[len + 1];
	}
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, tmp);
	line = ft_strjoin(line, " • ");
	return (line);
}

void	get_next_input(char **line, char **env)
{
	if (*line != NULL)
	{
		safe_free(line);
		*line = NULL;
	}
	*line = readline(prompt(env));
	if (!*line)
		exit (g_sig.exit_status);
	if (*line && **line)
		add_history(*line);
}
