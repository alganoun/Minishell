/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:42:10 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/31 15:37:59 by musoufi          ###   ########lyon.fr   */
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

int static	is_forbiden_name(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			if (str[i] == '_' || str[i] == '?' || ft_isdigit(str[i]))
				g_sig.exit_status = 0;
			else
				g_sig.exit_status = 1;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int		unset_process(t_token *token, char ***env)
{
	int i;
	int index;
	int j;
	char **tab;

	i = 0;
	if (token->arg == NULL)
		return (TRUE);
	while (token->arg[i] != NULL)
	{
		if (is_forbiden_name(token->arg[i]) == TRUE)
			return (TRUE);
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
