/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/22 17:12:53 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		pipe_finder(char *str, t_token **token)
{
	int i;
	t_token *new;

	i = 0;
	if (str !=	NULL)
	{
		if (str[i] == '|' && str[i + 1] == '\0')
		{
			init_struct(&new);
			new->operator = ft_strdup(str);
			new->next = (*token)->next;
			(*token)->next = new;
			return (1);
		}
	}
	return (0);
}

int		redir_finder(char **tab, t_token **token) // à reduire
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (tab[i] != NULL)
	{
		if (is_redir(tab[i]) == 1)
		{
			if (tab[i + 1] == NULL)
				return (write_errors(REDIR_ERROR, NULL));
			if ((*token)->redir == NULL)
			{
				(*token)->redir = ft_malloc(sizeof(char *) * 3);
				(*token)->redir[0] = ft_strdup(tab[0]);
				(*token)->redir[1] = ft_strdup(tab[1]);
				(*token)->redir[2] = NULL;
			}
			else
			{
				reallocate_tab(&((*token)->redir), tab[0]);
				reallocate_tab(&((*token)->redir), tab[1]);
			}
			return (1);
		}
	}
	return (0);
}

void	 option_finder(char *str, t_token **token)
{
	int i;

	i = 0;
	if (str !=	NULL)
	{
		if (str[i] == '"') // il faut que je regarde pour mieux parser les options.
			i++;
		if ((ft_strcmp((*token)->cmd, "echo") != 0
			&& str[i] == '-' && str[i + 1] != '\0')
				|| (ft_strcmp((*token)->cmd, "echo") == 0
					&& ft_strcmp(str, "-n") == 0))
		{
			if ((*token)->option == NULL)
			{
				(*token)->option = (char **)ft_malloc(sizeof(char *) * 2);
				(*token)->option[0] = ft_strdup(str);
				(*token)->option[1] = NULL;
			}
			else
				reallocate_tab(&((*token)->option), str);
		}
	}
}

void	global_variable_finder(char **str, char **env)
{
	int i;

	i = 0;
	char *new_str;
	while (env[i] != NULL)
	{
		if (strncmp(*str, env[i], ft_strlen(*str)) == 0)
		{
			new_str = ft_strdup(env[i] + ft_strlen(*str) + 1);
			safe_free(str);
			*str = new_str;
		}
	}
}

void	arg_finder(char *str, t_token **token)
{
	int i;

	i = 0;
	if (str !=	NULL)
	{
		if (str[i] == '"')  //gérer les erreurs de guilllemets ouverts ici
			i++;
		if ((ft_strcmp((*token)->cmd, "echo") == 0
			&& ft_strcmp(str, "-n") != 0)
			|| str[i] != '-' || (ft_strcmp((*token)->cmd, "cd") == 0
			&& ft_strcmp(str, "-") == 0))
		{
			if ((*token)->arg == NULL)
			{
				(*token)->arg= (char **)ft_malloc(sizeof(char *) * 2);
				(*token)->arg[0] = str;
				(*token)->arg[1] = NULL;
			}
			else
				reallocate_tab(&((*token)->arg), str);
		}
	}
}
