/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 14:17:24 by musoufi           #+#    #+#             */
/*   Updated: 2021/10/03 11:54:41 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	clean_redir(t_token *token, int savein, int saveout1, int saveout2)
{
	if (token->type == IN || token->type == INDEL)
		dup2(savein, 0);
	if (token->type == TRUNC || token->type == APPEND)
		dup2(saveout1, 1);
	if (token->type == ERR)
		dup2(saveout2, 2);
}

void	redir_dup2(int *tokenstd, int *save, int std)
{
	*save = dup(std);
	close(std);
	dup2(*tokenstd, std);
}

void	redir_dup(t_token *token, t_shell **shell, int pipe)
{
	int		savein;
	int		saveout1;
	int		saveout2;

	savein = 0;
	saveout1 = 0;
	saveout2 = 0;
	if (token->type == IN || token->type == INDEL)
		redir_dup2(&token->std, &savein, 0);
	if (token->type == TRUNC || token->type == APPEND)
		redir_dup2(&token->std, &saveout1, 1);
	if (token->type == ERR)
		redir_dup2(&token->std, &saveout2, 1);
	execution(token, shell, pipe);
	clean_redir(token, savein, saveout1, saveout2);
}

void	redirection(t_token *token, t_shell **shell, int pipe)
{
	int	i;
	int	j;

	i = 0;
	j = count_redir(token->redir);
	token->type = set_type(token->redir[i]);
	while (token->type)
	{
		if (token->type == TRUNC)
			token->std = open(token->redir[i + 1], \
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (token->type == APPEND)
			token->std = open(token->redir[i + 1], \
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		else if (token->type == IN)
			token->std = open(token->redir[i + 1], O_RDONLY, S_IRWXU);
		else if (token->type == INDEL)
			token->std = open(token->redir[i + 1], O_RDONLY, S_IRWXU);
		if (j <= 1)
			redir_dup(token, shell, pipe);
		i += 2;
		token->type = set_type(token->redir[i]);
		j--;
	}
}
