/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:29:30 by musoufi           #+#    #+#             */
/*   Updated: 2021/09/27 15:37:07 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_type(char *redir)
{
	if (redir == NULL)
		return (0);
	if (strncmp(redir, ">", 2) == 0)
		return (TRUNC);
	else if (strncmp(redir, ">>", 3) == 0)
		return (APPEND);
	else if (strncmp(redir, "<", 2) == 0)
		return (IN);
	else if (strncmp(redir, "<<", 3) == 0)
		return (INDEL);
	return (0);
}

int	count_redir(char **redir)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (redir[i])
	{
		if (strncmp(redir[i], ">>\0", 3) == 0)
			j++;
		else if (strncmp(redir[i], ">\0", 2) == 0)
			j++;
		i += 2;
	}
	return (j);
}
