/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:06:00 by alganoun          #+#    #+#             */
/*   Updated: 2021/09/10 18:13:10 by allanganoun      ###   ########lyon.fr   */
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
	int i;

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
	t_token *next;
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

void	free_env(t_shell **shell)
{
	free_tab(&((*shell)->env));
	free(*shell);
}

int		exit_free(t_token **token, char **line)
{
	free_struct(token);
	safe_free(line);
	return (-1);
}