/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 21:30:25 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/04 01:43:49 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_filler(char **pre_token, t_token **token, char **env, int option)
{
	if (option == 1)
		if (redir_finder(pre_token, token) == -1)
			return (-1);
	if (ft_strchr(pre_token[0], '$') != NULL || pre_token[0][0] == '~')
		get_variable_value(&(pre_token[0]), env);
	if (quote_remover(&(pre_token[0])) == -1)
		return (-1);
	if (option == 1)
		(*token)->cmd = pre_token[0];
	if (option == 2)
	{
		if (option_finder(pre_token[0], token) == 0)
			arg_finder(pre_token[0], token);
	}
	return (SUCCESS);
}

int	redir_management(char **str, t_token **token, char **env, int *i)
{
	int	res;

	res = redir_finder(str, token);
	if (res > 0)
		(*i)++;
	else if (res == -1)
		return (-1);
	else
		token_filler(str, token, env, 2);
	return (0);
}

int	input_process3(char **pre_token, t_token **token, char **env)
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
		&& token_filler(pre_token, token, env, 1) == -1)
		return (-1);
	while (pre_token && pre_token[i] != NULL && ft_strlen(pre_token[i]) > 0)
	{
		if (pipe_finder(pre_token[i], token) == 1)
		{
			if (input_process3(&(pre_token[++i]), token, env) == -1)
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
	char	**pre_token;

	i = 0;
	if (space_into_dot(line) == -1)
		return (-1);
	while ((*line)[i] == 13)
		i++;
	if ((*line)[i] == '\0')
	{
		safe_free(line);
		return (-1);
	}
	pre_token = ft_split(*line, 13);
	if (input_process2(pre_token, token, env) == -1)
		return (-1);
	free(pre_token);
	pre_token = NULL;
	return (0);
}
