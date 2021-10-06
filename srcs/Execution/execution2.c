/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:15:22 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/06 15:17:01 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	status_child(void)
{
	if (WIFEXITED(g_sig.pid))
		g_sig.exit_status = WEXITSTATUS(g_sig.pid);
	if (WIFSIGNALED(g_sig.pid))
	{
		g_sig.exit_status = WTERMSIG(g_sig.pid);
		if (g_sig.exit_status != 131)
			g_sig.exit_status += 128;
	}
}

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
	char	*tmp;

	i = 0;
	sum = 0;
	path = strenv("PATH", (*shell)->env);
	while (path[i])
		sum += ft_strlen(path[i++]);
	i = 0;
	tab = ft_malloc(sizeof(char *) * (sum + ((2 + ft_strlen(cmd)) * i)));
	if (tab == NULL)
		return (NULL);
	while (path[i])
	{
		tab[i] = ft_strjoin(path[i], "/");
		tmp = tab[i];
		tab[i] = ft_strjoin(tmp, cmd);
		safe_free(&tmp);
		i++;
	}
	free_tab(&path);
	return (tab);
}
