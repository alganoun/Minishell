/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:00:24 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/03 12:35:34 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	write_errors4(int option, char *str)
{
	if (option == IS_DIRECTORY)
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else if (option == PERM_DENIED)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (option == REDIR_ERROR2)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		g_sig.exit_status = 2;
	}
	return (-1);
}

int	write_errors3(int option, char *str)
{
	if (option > 8)
		g_sig.exit_status = 126;
	if (option == NOT_VALID_OPT)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		write(STDERR_FILENO, str, 2);
		ft_putendl_fd(": not a valid option", STDERR_FILENO);
		g_sig.exit_status = 2;
	}
	else if (option == NOFILEORDIR)
	{
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_sig.exit_status = 127;
	}
	else if (option > 8)
	{
		g_sig.exit_status = 126;
		write_errors4(option, str);
	}
	return (-1);
}

int	write_errors2(int option, char *str)
{
	if (option == REDIR_ERROR)
	{
		ft_putstr_fd("syntax error near unexpected token `",
			STDERR_FILENO);
		if (str[0] == '|')
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
		if (g_sig.exit_status == -1)
			g_sig.exit_status = 1;
	}
	else if (option > 6)
		return (write_errors3(option, str));
	return (-1);
}

int	write_errors(int option, char *str)
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

void	fd_write_errors(t_token *token)
{
	DIR	*dir;
	int	fd;

	fd = open(token->cmd, O_WRONLY);
	dir = opendir(token->cmd);
	if (ft_strchr(token->cmd, '/') == NULL)
		write_errors(WRONG_CMD, token->cmd);
	else if (fd == -1 && dir == NULL)
		write_errors(NOFILEORDIR, token->cmd);
	else if (fd == -1 && dir != NULL)
		write_errors(IS_DIRECTORY, token->cmd);
	else if (fd != -1 && dir == NULL)
		write_errors(PERM_DENIED, token->cmd);
	if (dir)
		closedir(dir);
	if (fd > 0)
		close(fd);
}
