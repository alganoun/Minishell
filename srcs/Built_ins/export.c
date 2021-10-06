/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:34:34 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 01:28:19 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_assign_operator(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i])
	{
		if (str[i] != '=' || str[i] == 0)
			return (FALSE);
		i--;
	}
	return (TRUE);
}

void	export_process2(char ***env, char **str, char **tab)
{
	if (check_name(*str) == 0 && is_assign_operator(*str) == FALSE)
		g_sig.exit_status = 0;
	if (is_exportable(*str) == 0)
	{
		if (is_assign_operator(*str) == TRUE)
			g_sig.exit_status = 1;
		write_errors(6, *str);
	}
	else if (check_name(*str) > 0 && variable_existence(*str, tab) > 0)
	{
		free((*env)[variable_existence(*str, tab)]);
		(*env)[variable_existence(*str, tab)] = ft_strdup(*str);
	}
	else
		reallocate_tab(env, *str);
}

int	export_process(t_token *token, char ***env)
{
	int		i;
	char	*str;
	char	**tab;

	i = 0;
	tab = export_name_tab(*env);
	if (token->option)
		return (write_errors5(token->cmd, token->option[0], 1));
	if (token->arg == NULL || token->arg[0][0] == '\0')
		print_sorted_tab(*env);
	else
	{
		while (token->arg && token->arg[i] != NULL)
		{
			str = ft_strdup(token->arg[i]);
			export_process2(env, &str, tab);
			i++;
		}
	}
	free_tab(&tab);
	if (g_sig.exit_status == -1)
		g_sig.exit_status = 0;
	return (TRUE);
}
