/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:28:32 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/01 17:32:33 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_errors(t_token *token)
{
	write(2, "Minishell: ", 11);
	write(2, token->arg[0], ft_strlen(token->arg[0]));
	write(2, ": No such file or directory\n", 28);
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

void	replace_old_dir(char **env_str, char *old_dir)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_dir);
	safe_free(env_str);
	*env_str = tmp;
	tmp = NULL;
}

void	go_to_dir(t_token *token, char ***env)
{
	char	*dir;

	dir = NULL;
	if (ft_strcmp(*token->arg, "-") == 0 || token->arg == NULL)
	{
		if (chdir(my_getenv("OLDPWD", *env)) != 0)
			write_cd_errors(token);
		if (ft_strcmp(*token->arg, "-") == 0)
		{
			dir = getcwd(NULL, 0);
			write_output(dir);
			safe_free(&dir);
		}
	}
	else if (chdir(token->arg[0]) != 0)
		write_cd_errors(token);
}

void	cd_process(t_token *token, char ***env)
{
	int		i;
	char	*old_dir;

	old_dir = getcwd(NULL, 0);
	i = 0;
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
			replace_old_dir(&((*env)[i]), old_dir);
		i++;
	}
	safe_free(&old_dir);
}
