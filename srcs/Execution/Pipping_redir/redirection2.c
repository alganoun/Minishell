/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:29:30 by musoufi           #+#    #+#             */
/*   Updated: 2021/09/27 15:37:07 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	set_type(char *redir)
{
	if (redir == NULL)
		return (0);
	if (strncmp(redir, ">", 2) == 0)
		return (TRUNC);
	else if (strncmp(redir, ">>", 3) == 0)
		return (APPEND);
	else if (strncmp(redir, "<", 2) == 0)
		return (IN);
	else if (strncmp(redir, "<<", 3) == 0)
		return (INDEL);
	return (0);
}

int	count_redir(char **redir)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (redir[i])
	{
		if (strncmp(redir[i], ">>\0", 3) == 0)
			j++;
		else if (strncmp(redir[i], ">\0", 2) == 0)
			j++;
		i += 2;
	}
	return (j);
}

int	heredoc(t_token *token)
{
	char 	*line;
	char	*limiter;
	char	*prompt_line;
	int 	fd[2];
	size_t	len;

	pipe(fd);
	limiter = token->redir[1];
	len = ft_strlen(limiter);
	prompt_line = ft_strdup("> ");
	while (ft_strncmp(line, limiter, len) != 0)
	{
		line = readline(prompt_line);
		ft_strjoin(line, "x");
		len = ft_strlen(line);
		if (ft_strncmp(line, limiter, len) != 0)
			write(fd[1], line, len);
	}
	char *buffer;
	buffer = malloc(BUFSIZ);
	read(fd[0], buffer, BUFSIZ);
   	printf("pipe=%s\n", buffer);
	safe_free(&prompt_line);
	close(fd[1]);
	return (fd[0]);
}