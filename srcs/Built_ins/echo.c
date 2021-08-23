/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:42:11 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/23 20:18:52 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int		echo_process(t_token *token, char **env)
// {
	// int i;
	// int j;
	// char quote;
//
	// i = 0;
	// quote = '\0';
	// while (token->arg[i] != NULL)
	// {
		// j = 0;
		// if (token->arg[i][0] == '"' || token->arg[i][0] == '\'')
			// quote = token->arg[i][0];
		// while (token->arg[i][j])
		// {
			// if (token->arg[i][j] == '$')
				// j = write_variable(&(token->arg[i][j + 1]), quote, env) + j + 1;
			// write (1, &(token->arg[i][j]), 1);
			// j++;
		// }
		// if (token->arg[i + 1] != NULL)
			// write(1, " ", 1);
		// i++;
	// }
	// if (token->option == NULL)
		// write(1, "\n", 1);
	// return (TRUE);
// }

void	echo_write(t_token *token, char *str, int i)
{
	write (1, str, ft_strlen(str));
	if (token->arg[i + 1] != NULL)
		write (1, " ", 1);
}

int		echo_process(t_token *token, char **env)
{
	int i;
	char *str;

	i = 0;
	while (token->arg && token->arg[i] != NULL)
	{
		quote_remover(&(token->arg[i]), &token);
		str = ft_strdup(token->arg[i]);
		if (token->exp == 0)
			get_variable_value(&str, env);
		echo_write(token, str, i);
		safe_free(&str);
		i++;
	}
	i = 0;
	if (token->option)
	{
		while (ft_strcmp(token->option[i], "-n") != 0)
			i++;
		if (token->option[i] == NULL)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (TRUE);
}
