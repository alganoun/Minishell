/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:42:10 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 18:27:58 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_env(char ***env, char ***tab)
{
	free_tab(env);
	*env = *tab;
	*tab = NULL;
}

void	unset_process2(t_token *token, char ***env, int i)
{
	int		j;
	int		index;
	char	**tab;

	index = 0;
	j = count_to_keep(token->arg[i], *env);
	tab = (char **)ft_malloc(sizeof(char *) * (j + 1));
	j = 0;
	while ((*env)[index])
	{
		if (ft_strncmp(token->arg[i],
				(*env)[index], equal_detection((*env)[index])) != 0)
			tab[j++] = ft_strdup((*env)[index]);
		index++;
	}
	tab[j] = NULL;
	replace_env(env, &tab);
}

int	unset_process(t_token *token, char ***env)
{
	int		i;

	i = 0;
	if (token->arg == NULL)
		return (TRUE);
	while (token->arg[i] != NULL)
	{
		if (is_forbiden_name(token->arg[i]) == TRUE)
			return (TRUE);
		unset_process2(token, env, i);
		i++;
	}
	return (TRUE);
}
