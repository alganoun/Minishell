/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:28:32 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/06 02:10:24 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_errors(t_token *token, int option)
{
	if (option == 1)
		ft_putendl_fd("Minishell: cd: OLDPWD not set", STDERR_FILENO);
	else if (option == 2)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, token->arg[0], ft_strlen(token->arg[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
	g_sig.exit_status = 1;
}

void	go_to_dir(t_token *token, char ***env)
{
	char	*dir;

	dir = NULL;
	if (token->arg == NULL)
	{
		dir = my_getenv("HOME", *env);
		if (chdir(dir) != 0)
			write_cd_errors(token, 2);
		safe_free(&dir);
	}
	else if (ft_strcmp(*token->arg, "-") == 0)
	{
		if (my_getenv("OLDPWD", *env) == NULL)
			write_cd_errors(token, 1);
		else if (chdir(my_getenv("OLDPWD", *env)) == 0)
		{
			dir = getcwd(NULL, 0);
			write_output(dir);
			safe_free(&dir);
		}
		else
			write_cd_errors(token, 2);
	}
	else if (chdir(token->arg[0]) != 0)
		write_cd_errors(token, 2);
}

void	cd_process_current(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
			replace_current_dir(&((*env)[i]));
		i++;
	}
}

void	cd_process_old(char ***env, char *old_dir)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
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

int	cd_process(t_token *token, char ***env)
{
	char	*old_dir;

	old_dir = getcwd(NULL, 0);
	if (token->option)
		return (write_errors5(token->cmd, token->option[0], 2));
	go_to_dir(token, env);
	cd_process_current(env);
	cd_process_old(env, old_dir);
	return (TRUE);
}
