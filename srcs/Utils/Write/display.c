/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/03 12:15:44 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

ssize_t	write_output(char *str)
{
	return ((write(1, str, ft_strlen(str))) + (write(1, "\n", 1)));
}

int	display_txt(char *str)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		while (ret > 0)
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

char	*prompt2(char **tmp2, char **tmp, char **line)
{
	*tmp2 = ft_strjoin(*line, " ");
	safe_free(line);
	*line = ft_strjoin(*tmp2, *tmp);
	safe_free(tmp2);
	safe_free(tmp);
	*tmp2 = ft_strjoin(*line, " • ");
	safe_free(line);
	return (*tmp2);
}

char	*prompt(char **env)
{
	char	*tmp;
	char	*tmp2;
	char	*line;
	size_t	len;

	tmp2 = ft_strjoin("[", my_getenv("USER", env));
	line = ft_strjoin(tmp2, "]");
	safe_free(&tmp2);
	tmp2 = getcwd(NULL, 0);
	tmp = ft_strjoin("/Users/", my_getenv("USER", env));
	if (ft_strcmp(tmp2, tmp) == 0)
	{
		safe_free(&tmp);
		tmp = ft_strdup("~");
	}
	else
	{
		safe_free(&tmp);
		len = ft_strlen(tmp2);
		while (tmp2[len] != '/')
			len--;
		tmp = ft_strdup(&tmp2[len + 1]);
	}
	safe_free(&tmp2);
	return (prompt2(&tmp2, &tmp, &line));
}

void	get_next_input(char **line, char **env)
{
	char	*prompt_line;

	prompt_line = prompt(env);
	*line = readline(prompt_line);
	safe_free(&prompt_line);
	if (!*line)
		exit (g_sig.exit_status);
	if (*line && **line)
		add_history(*line);
}
