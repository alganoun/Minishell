/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 20:55:08 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 20:25:04 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	version_process(t_token *token)
{
	int	i;

	i = 0;
	while (token->option && token->option[i] != NULL)
	{
		if (ft_strcmp(token->option[i], "-version") == 0)
			display_txt("version.txt");
		i++;
	}
}
