/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 21:30:25 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/23 18:22:32 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		input_process2(char **pre_token, t_token **token)
{
	int i;
	t_token *new;

	i = 1;
	(*token)->cmd = pre_token[0];
	while (pre_token && pre_token[i] != NULL)
	{
		if (pipe_finder(pre_token[i], token) == 1)
		{
			i++;
			init_struct(&new);
			new->next = (*token)->next->next;
			(*token)->next->next = new;
			new->cmd = pre_token[i];
			*token = new;
		}
		else
		{
			if (redir_finder(&pre_token[i], token) > 0)
				i++;
			else
			{
				option_finder(pre_token[i], token);
				arg_finder(pre_token[i], token);
			}
		}
		i++;
	}
	return (0);
}

int		input_process(char *line, t_token **token)
{
	int i;
	int j;

	i = 0;
	char **pre_token;
	(void)token;
	j = 0;
	if (space_into_dot(&line) == -1)
		return (-1);
	pre_token = ft_split(line, 13);
	input_process2(pre_token, token);
	//token_cleaning(token);
	return (0);
}

int		parsing(char *line, t_token **token_list)
{
	int		i;
	t_token	*new;
	i = 0;

	if (*token_list != NULL)
	free_struct(token_list);
	init_struct(&new);
	token_add_back(token_list, &new);
	if (input_process(line, &new) == -1)
		return (-1);
	return(0);
}
