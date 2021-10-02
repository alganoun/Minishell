/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:06:00 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/03 01:14:51 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (*tab != NULL)
	{
		while ((*tab)[i] != NULL)
		{
			safe_free(&((*tab)[i]));
			i++;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_struct(t_token **token)
{
	t_token	*next;

	while ((*token)->next != NULL)
	{
		safe_free(&((*token))->cmd);
		safe_free(&((*token))->operator);
		free_tab(&((*token))->option);
		free_tab(&((*token))->arg);
		free_tab(&((*token))->redir);
		next = (*token)->next;
		free(*token);
		*token = NULL;
		*token = next;
	}
	safe_free(&(*token)->cmd);
	safe_free(&((*token))->operator);
	free_tab(&(*token)->option);
	free_tab(&(*token)->arg);
	free_tab(&((*token))->redir);
	free((*token));
	*token = NULL;
}
