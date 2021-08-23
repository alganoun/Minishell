/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:53:22 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/23 20:16:04 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		init_struct(t_token **token)
{
	*token = (t_token *)ft_malloc(1 * sizeof(t_token));
	if (!(*token))
		return (-1);
	**token = (t_token){
		.cmd = NULL,
		.redir = NULL,
		.option = NULL,
		.exp = 0,
		.arg = NULL,
		.operator = NULL,
		.next = NULL,
		.type = 0,
		.std = 0,
		.in = 0,
		.out = 0,
		.ret = 0,
		.pid_index = 0,
		.pids = {0}
	};
	return (0);
}

t_token		*token_last(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **atoken, t_token **new)
{
	t_token *last;

	if (*atoken == NULL)
		*atoken = *new;
	else
	{
		last = token_last(*atoken);
		last->next = *new;
		(*new)->next = NULL;
	}
}

t_token	*token_new()
{
	t_token *token;

	init_struct(&token);
	return (token);
}

//void	token_cleaning(t_token **token)
//{
//	int i;
//
//	i = 0;
//
//	if ((*token)->cmd)
//		quote_remover(&((*token)->cmd));
//	while ((*token)->option && (*token)->option[i] != NULL)
//		quote_remover(&((*token)->option[i++]));
//	i = 0;
//	while ((*token)->arg && (*token)->arg[i] != NULL)
//		quote_remover(&((*token)->arg[i++]));
//	while ((*token)->redir && (*token)->redir[i] != NULL)
//		quote_remover(&((*token)->redir[i++]));
//	*token = (*token)->next;
//}
