/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:42:09 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 15:40:38 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_home(char **env)
{
	char	*dir;

	dir = my_getenv("HOME", env);
	if (chdir(dir) != 0)
		return (-1);
	safe_free(&dir);
	return (0);
}

void	replace_current_dir(char **env_str)
{
	char	*tmp;
	char	*dir;

	dir = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", dir);
	safe_free(&dir);
	safe_free(env_str);
	*env_str = tmp;
	tmp = NULL;
}

int	replace_old_dir(char **env_str, char *old_dir)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_dir);
	free_replace(env_str, &tmp);
	return (TRUE);
}
