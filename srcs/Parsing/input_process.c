/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/06 04:13:50 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_finder(char *str, t_token **token)
{
	int		i;
	t_token	*new;

	i = 0;
	if (str != NULL)
	{
		if (str[i] == '|' && str[i + 1] == '\0')
		{
			init_struct(&new);
			new->operator = str;
			new->next = (*token)->next;
			(*token)->next = new;
			return (1);
		}
	}
	return (0);
}

void	redir_finder2(char **tab, t_token **token)
{
	(*token)->redir = ft_malloc(sizeof(char *) * 3);
	(*token)->redir[0] = tab[0];
	(*token)->redir[1] = tab[1];
	(*token)->redir[2] = NULL;
}

int	redir_finder(char **tab, t_token **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tab[i] != NULL)
	{
		if (is_redir(tab[i]) == 1)
		{
			if (tab[i + 1] == NULL || ft_strlen(tab[i + 1]) < 1)
				return (write_errors(REDIR_ERROR, "newline"));
			else if (tab[i + 1][0] == '>' || tab[i + 1][0] == '<')
				return (write_errors(REDIR_ERROR, &(tab[i + 1][0])));
			if ((*token)->redir == NULL)
				redir_finder2(tab, token);
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

int	option_finder(char *str, t_token **token)
{
	int	i;

	i = 0;
	if (str != NULL && (*token)->cmd != NULL && (*token)->arg == NULL)
	{
		if ((ft_strcmp((*token)->cmd, "echo") != 0
				&& str[i] == '-' && str[i + 1] != '\0')
			|| (ft_strcmp((*token)->cmd, "echo") == 0
				&& is_echo_option(str) == 1))
		{
			if ((*token)->option == NULL)
			{
				(*token)->option = (char **)ft_malloc(sizeof(char *) * 2);
				(*token)->option[0] = str;
				(*token)->option[1] = NULL;
			}
			else
				reallocate_tab(&((*token)->option), str);
			return (SUCCESS);
		}
	}
	return (FALSE);
}

void	arg_finder(char *str, t_token **token)
{
	int	i;

	i = 0;
	if (str != NULL && (*token)->cmd != NULL)
	{
		if (str || (ft_strcmp((*token)->cmd, "cd") == 0
				&& ft_strcmp(str, "-") == 0))
		{
			if ((*token)->arg == NULL)
			{
				(*token)->arg = (char **)ft_malloc(sizeof(char *) * 2);
				(*token)->arg[0] = str;
				(*token)->arg[1] = NULL;
			}
			else
				reallocate_tab(&((*token)->arg), str);
		}
	}
}
