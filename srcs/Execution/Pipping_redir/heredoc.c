/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:11:34 by musoufi           #+#    #+#             */
/*   Updated: 2021/10/06 15:14:22 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	search_for_heredoc(t_token *token, char **env)
{
	int	i;

	while (token)
	{
		i = 0;
		while (token->redir && token->redir[i]
			&& ft_strncmp(token->redir[i], "<<", 3) == 0)
		{
			if (token->std > 2)
				close(token->std);
			token->std = heredoc(token, env, token->redir[i + 1]);
			i += 2;
		}
		token = token->next;
	}
}
