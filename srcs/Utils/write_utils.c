/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:00:24 by alganoun          #+#    #+#             */
/*   Updated: 2021/09/29 23:26:14 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t		write_output(char *str)
{
	return ((write(1, str, ft_strlen(str))) + (write(1, "\n", 1)));
}

int		write_errors3(int option)
{
	if (option == NOFILEORDIR)
	{
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_sig.exit_status = 127;
	}
	else if (option == IS_DIRECTORY)
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else if (option == PERM_DENIED)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	if (option > 8)
		g_sig.exit_status = 126;
	return (-1);
}

int		write_errors2(int option, char *str)
{
	if (option == REDIR_ERROR)
	{
		ft_putstr_fd("syntax error near unexpected token `",STDERR_FILENO);
		if(str[0] == '>' || str[0] == '<')
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		g_sig.exit_status = 2;
	}
	else if (option == VAR_NOT_FOUND)
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
	}
	else if (option == NOT_VALID_OPT)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		write(STDERR_FILENO, str, 2);
		ft_putendl_fd(": not a valid option", STDERR_FILENO);
	}
	else if (option > 7)
		return (write_errors3(option));
	return (-1);
}

int		write_errors(int option, char *str)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	if (option == BAD_CHAR)
		ft_putendl_fd("use of unsupported character", STDERR_FILENO);
	else if (option == WRONG_CMD)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		g_sig.exit_status = 127;
	}
	else if (option == BAD_QUOTES)
		ft_putendl_fd("Quotes open, close them", STDERR_FILENO);
	else if (option == PATH_ERROR)
		ft_putendl_fd("PATH error", STDERR_FILENO);
	else if (option > 4)
		return (write_errors2(option, str));
	return (-1);
}

void	fd_write_errors(char *cmd)
{
	DIR	*dir;
	int	fd;

	fd = open(cmd, O_WRONLY);
	dir = opendir(cmd);
	if (ft_strchr(cmd, '/') == NULL)
		write_errors(WRONG_CMD, cmd);
	else if (fd == -1 && dir == NULL)
		write_errors(NOFILEORDIR, cmd);
	else if (fd == -1 && dir != NULL)
		write_errors(IS_DIRECTORY, cmd);
	else if (fd != -1 && dir == NULL)
		write_errors(PERM_DENIED, cmd);
	if (dir)
		closedir(dir);
	if (fd > 0)
		close(fd);
}

int		write_variable(char *str, char c, char **env)
{
	int i;
	char *var;
	char *result;

	i = 0;
	while (str[i] != c && str[i] != ' ')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (str[i] != c && str[i] != ' ')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	result = my_getenv(var, env);
	if (result)
		write (1, result, ft_strlen(result));
	return (i);
}
