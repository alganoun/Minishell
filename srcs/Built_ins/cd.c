/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:28:32 by allanganoun       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/04 04:29:34 by allanganoun      ###   ########lyon.fr   */
=======
/*   Updated: 2021/10/03 13:06:46 by musoufi          ###   ########lyon.fr   */
>>>>>>> 382cd3508699b57a689ec4033f4d6b23acada166
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_errors(t_token *token)
{
	write(2, "Minishell: ", 11);
	write(2, token->arg[0], ft_strlen(token->arg[0]));
	write(2, ": No such file or directory\n", 28);
	g_sig.exit_status = 1;
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

void	go_to_dir(t_token *token, char ***env)
{
	char	*dir;

	dir = NULL;
	if (token->arg == NULL)
	{
		dir = ft_strjoin("/Users/", my_getenv("USER", *env));
		if (chdir(dir) != 0)
			write_cd_errors(token);
		safe_free(&dir);
	}
	else if (ft_strcmp(*token->arg, "-") == 0)
	{
		if (chdir(my_getenv("OLDPWD", *env)) != 0)
			write_cd_errors(token);
		dir = getcwd(NULL, 0);
		write_output(dir);
		safe_free(&dir);
	}
	else if (chdir(token->arg[0]) != 0)
		write_cd_errors(token);
}

void	cd_process(t_token *token, char ***env)
{
	int		i;
	int		ret;
	char	*old_dir;

	g_sig.exit_status = 0;
	old_dir = getcwd(NULL, 0);
	i = 0;
	ret = 0;
	go_to_dir(token, env);
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
			replace_current_dir(&((*env)[i]));
		i++;
	}
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "OLDPWD=", 7) == 0)
			ret = replace_old_dir(&((*env)[i]), old_dir, 1, env);
		i++;
	}
	if (ret != TRUE)
		replace_old_dir(&((*env)[i]), old_dir, 2, env);
	safe_free(&old_dir);
}
