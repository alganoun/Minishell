/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:42:10 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 15:09:02 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_env(char ***env, char ***tab)
{
	free_tab(env);
	*env = *tab;
	*tab = NULL;
}

int	is_unsetable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 32 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95)
			|| str[i] == '`' || str[i] == 123
			|| str[i] == 125 || str[i] == 36 || str[i] == 126)
		{
			g_sig.exit_status = 1;
			return (FALSE);
		}
		i++;
	}
	return (SUCCESS);
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
	g_sig.exit_status = 0;
	if (token->option)
		return (write_errors5(token->cmd, token->option[0], 1));
	if (token->arg == NULL)
		return (TRUE);
	while (token->arg[i] != NULL)
	{
		if (is_unsetable(token->arg[i]) == 0)
			write_errors(6, token->cmd);
		else
			unset_process2(token, env, i);
		i++;
	}
	return (TRUE);
}
