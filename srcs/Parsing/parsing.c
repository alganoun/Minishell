/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 21:30:25 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 18:39:09 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		else
		{
			if (redir_finder(&pre_token[i], token) == -1)
				return (-1);
			else if (redir_finder(&pre_token[i], token) > 0)
				i++;
			else
				token_filler(pre_token[i], token, env, 2);
		}
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

int	parsing(char **line, t_token **token_list, char **env)
{
	int		i;
	t_token	*new;

	i = 0;
	if (*token_list != NULL)
		free_struct(token_list);
	init_struct(&new);
	token_add_back(token_list, &new);
	if (input_process(line, &new, env) == -1)
		return (-1);
	safe_free(line);
	return (0);
}
