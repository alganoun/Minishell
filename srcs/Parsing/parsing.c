/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 21:30:25 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/02 03:49:06 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_management(char **str, t_token **token, char **env, int *i)
{
	int	res;

	res = redir_finder(str, token);
	if (res > 0)
		(*i)++;
	else if (res == -1)
		return (-1);
	else
		token_filler(*str, token, env, 2);
	return (0);
}

int	token_filler(char *pre_token, t_token **token, char **env, int option)
{
	if (ft_strchr(pre_token, '$') != NULL)
		get_variable_value(&pre_token, env);
	if (quote_remover(&pre_token) == -1)
		return (-1);
	if (option == 1)
		(*token)->cmd = pre_token;
	if (option == 2)
	{
		if (option_finder(pre_token, token) == 0)
			arg_finder(pre_token, token);
	}
	return (SUCCESS);
}

int	input_process3(char *pre_token, t_token **token, char **env)
{
	t_token	*new;

	init_struct(&new);
	new->next = (*token)->next->next;
	(*token)->next->next = new;
	if (token_filler(pre_token, &new, env, 1) == -1)
		return (-1);
	*token = new;
	return (SUCCESS);
}

int	input_process2(char **pre_token, t_token **token, char **env)
{
	int	i;

	i = 1;
	if (ft_strlen(pre_token[0]) > 0
		&& token_filler(pre_token[0], token, env, 1) == -1)
		return (-1);
	while (pre_token && pre_token[i] != NULL && ft_strlen(pre_token[i]) > 0)
	{
		if (pipe_finder(pre_token[i], token) == 1)
		{
			if (input_process3(pre_token[++i], token, env) == -1)
				return (-1);
		}
		else if (redir_management(&pre_token[i], token, env, &i) == -1)
			return (-1);
		i++;
	}
	return (SUCCESS);
}

int	input_process(char **line, t_token **token, char **env)
{
	int		i;
	int		j;
	char	**pre_token;

	i = 0;
	j = 0;
	if (space_into_dot(line, env) == -1)
		return (-1);
	pre_token = ft_split(*line, 13);
	if (input_process2(pre_token, token, env) == -1)
		return (-1);
	free(pre_token);
	pre_token = NULL;
	return (0);
}
