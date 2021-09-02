/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:28:32 by allanganoun       #+#    #+#             */
/*   Updated: 2021/09/02 11:53:34 by allanganoun      ###   ########lyon.fr   */
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
	char *tmp;

	tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
	safe_free(env_str);
	*env_str = tmp;
}

void	replace_old_dir(char **env_str, char *old_dir)
{
	char *tmp;

	tmp = ft_strjoin("OLDPWD=", old_dir);
	safe_free(env_str);
	*env_str = tmp;
}

void	go_to_dir(t_token *token, char ***env)
{
		if (token->arg == NULL || ft_strcmp(*token->arg, "~") == 0)
		{
			if (chdir(ft_strjoin("/Users/", my_getenv("USER", *env))) != 0)
				write_cd_errors(token);
		}
		else if (ft_strcmp(*token->arg, "-") == 0 || token->arg == NULL)
		{
			if (chdir(my_getenv("OLDPWD", *env)) != 0)
				write_cd_errors(token);
			if (ft_strcmp(*token->arg, "-") == 0)
				write_output(getcwd(NULL,0));
		}
		else if (chdir(token->arg[0]) != 0)
			write_cd_errors(token);
}

void	cd_process(t_token *token, char ***env)
{
	int i;
	char *old_dir;

	old_dir = ft_strdup(getcwd(NULL, 0));
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
}
