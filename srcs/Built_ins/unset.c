/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:42:10 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/24 01:07:21 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		equal_detection(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int		count_to_keep(char *str, char **env)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], equal_detection(env[i])) != 0)
			count++;
		i++;
	}
	return (count);
}

int		unset_process(t_token *token, char ***env) // il faut encore faire des tests dessus
{
	int i;
	int index;
	int j;
	char **tab;

	i = 0;
	while (token->arg[i] != NULL)
	{
		index = 0;
		j = count_to_keep(token->arg[i], *env);
		tab = (char **)ft_malloc(sizeof(char *) * (j + 1));
		j = 0;
		while ((*env)[index])
		{
			if (ft_strncmp(token->arg[i]
				, (*env)[index], equal_detection((*env)[index])) != 0)
				tab[j++] = ft_strdup((*env)[index]);
			index++;
		}
		tab[j] = NULL;
		free_tab(env);
		*env = tab;
		tab = NULL;
		i++;
	}
	return (TRUE);
}
