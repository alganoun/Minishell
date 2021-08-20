/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/20 16:12:04 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *prompt(void)
{
	char *tmp;
	char *line;
	size_t len;

	line = ft_strjoin("[", getenv("USER"));
	line = ft_strjoin(line, "]");
	tmp = getcwd(NULL, 0);
	if (ft_strcmp(tmp, ft_strjoin("/Users/", getenv("USER"))) == 0) // il faut faire gaffe à utiliser notre env et pas celui du zsh
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

void	get_next_input(char **line)
{
	if (*line != NULL)
	{
		safe_free(line);
		*line = NULL;
	}
	*line = readline(prompt());
	if (!*line)
		exit (g_sig.exit_status);
	if (*line && **line)
		add_history(*line);
}
