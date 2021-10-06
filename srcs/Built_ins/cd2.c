/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:42:09 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 02:38:16 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_home(char **env)
{
	char *dir;

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

int	replace_old_dir(char **env_str, char *old_dir, int option, char ***env)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_dir);
	if (option == 1)
		free_replace(env_str, &tmp);
	else if (option == 2)
		reallocate_tab(env, tmp);
	return (TRUE);
}
