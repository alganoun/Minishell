/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:39 by musoufi           #+#    #+#             */
/*   Updated: 2021/08/19 12:57:13 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*build_line(char **tab, char *line)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		line = ft_strjoin(line, tab[i]);
		line = ft_strjoin(line, " ");
		i++;
	}
	return (line);
}

char	**build_cmd(t_token *token)
{
	char	**cmd;
	char	*line;

	if (token->option == NULL && token->arg == NULL)
		return (ft_split(token->cmd, ' '));
	line = ft_strjoin(token->cmd, " ");
	if (token->option)
		line = build_line(token->option, line);
	if (token->arg)
		line = build_line(token->arg, line);
	cmd = ft_split(line, ' ');
	free(line);
	return (cmd);
}

char	**bin(t_shell **shell, char *cmd)
{
	int		i;
	int		sum;
	char	**path;
	char	**tab;

	i = 0;
	sum = 0;
	path = strenv("PATH", (*shell)->env);
	while (path[i])
	{
		sum += ft_strlen(path[i]);
		i++;
	}
	i = 0;
	tab = malloc(sizeof(char *) * (sum + ((2 + ft_strlen(cmd)) * i)));
	if (tab == NULL)
		return (NULL);
	while (path[i])
	{
		tab[i] = ft_strjoin(path[i], "/");
		tab[i] = ft_strjoin(tab[i], cmd);
		i++;
	}
	return (tab);
}

void	exec_cmd(t_token *token, t_shell **shell)
{
	int			i;
	char		**tab;
	char		**cmd;
	struct stat	buf;

	i = 0;
	cmd = build_cmd(token);
	tab = bin(shell, cmd[0]);
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		if (stat(tab[i], &buf) == 0)
			execve(tab[i], cmd, (*shell)->env);
		i++;
	}
	token->ret = fd_write_errors(token->cmd);
	exit_prog(&token, NULL, token->ret);
}

void	exec_cmd_fork(t_token *token, t_shell **shell)
{
	int			i;
	char		**tab;
	char		**cmd;
	struct stat	buf;

	i = 0;
	cmd = build_cmd(token);
	tab = bin(shell, cmd[0]);
	g_sig.pid = fork();
	if (g_sig.pid < 0)
		ft_putstr_fd("fail\n", 2);
	else if (!g_sig.pid)
	{
		while (tab[i])
		{
			if (stat(tab[i], &buf) == 0)
				execve(tab[i], cmd, (*shell)->env);
			i++;
		}
		token->ret = fd_write_errors(token->cmd);
		exit_prog(&token, NULL, token->ret);
	}
	wait(&g_sig.pid);
}
