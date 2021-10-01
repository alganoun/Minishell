/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:34:34 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 18:27:09 by alganoun         ###   ########.fr       */
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

void	export_process3(t_token *token, char ***env, char **str)
{
	if (token->exp == 1)
		get_variable_value(str, *env);
	reallocate_tab(env, *str);
}

void	export_process2(t_token *token, char ***env, char **str, char **tab)
{
	if (check_name(*str) == 0 && is_assign_operator(*str) == FALSE)
		g_sig.exit_status = 0;
	else if (variable_existence(*str, tab) > 0 && check_name(*str) > 0)
	{
		free((*env)[variable_existence(*str, tab)]);
		(*env)[variable_existence(*str, tab)] = ft_strdup(*str);
	}
	else if (is_exportable(*str) == 0)
	{
		is_forbiden_name(*str);
		if (is_assign_operator(*str) == TRUE)
			g_sig.exit_status = 1;
		write_errors(6, &((*str)[check_name(*str)]));
	}
	else if (is_forbiden_name(*str) == TRUE)
	{
		if (is_assign_operator(*str) == TRUE)
			g_sig.exit_status = 1;
		write_errors(6, &((*str)[check_name(*str)]));
	}
	else
		export_process3(token, env, str);
}

int	export_process(t_token *token, char ***env)
{
	int		i;
	char	*str;
	char	**tab;

	i = 0;
	tab = export_name_tab(*env);
	if (token->option)
		return (write_errors(NOT_VALID_OPT, token->option[0]));
	if (token->arg == NULL || token->arg[0][0] == '\0')
		print_sorted_tab(*env);
	else
	{
		while (token->arg && token->arg[i] != NULL)
		{
			str = ft_strdup(token->arg[i]);
			export_process2(token, env, &str, tab);
			i++;
		}
	}
	free_tab(&tab);
	return (TRUE);
}
