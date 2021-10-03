/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:07:38 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/03 11:53:10 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env(t_shell **shell)
{
	free_tab(&((*shell)->env));
	free(*shell);
}

int	exit_free(t_token **token, char **line)
{
	free_struct(token);
	safe_free(line);
	return (-1);
}

void	free_replace(char **str, char **new)
{
	safe_free(str);
	*str = *new;
	*new = NULL;
}
