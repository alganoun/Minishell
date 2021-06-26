/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/26 17:03:06 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_all(t_token *token)
{
	printf("CMD : %s\n", token->cmd);
	if (token->option != NULL)
		for (int i = 0 ; token->option[i] != NULL ; i++)
			printf("OPTION = %s\n", token->option[i]);
	if (token->arg != NULL)
		for (int i = 0 ; token->arg[i] != NULL ; i++)
			printf("ARG = %s\n", token->arg[i]);
}

int		display_txt(char *str)
{
	int fd;
	int ret;
	char *line;
	ret = 1;

	fd = open(str, O_RDONLY);
	printf("%d\n", fd);
	if (fd > 0)
	{
		while(ret > 0)
		{
			ret = get_next_line(fd, &line);
			write_output(line);
			free(line);
		}
		ret = get_next_line(fd, &line);
		write_output(line);
		free(line);
	}
	if (ret != 0)
		return (write_errors(1, str));
	return (0);
}

int		input_process2(char **pre_token, t_token **token)
{
	int i;

	i = 1;
	(*token)->cmd = pre_token[0];
	while (pre_token[i] != NULL)
	{
		option_finder(pre_token[i], token);
		arg_finder(pre_token[i], token);
		i++;
	}
	return (0);
}

int		input_process(char **tab, t_token **token)
{
	int i;
	int j;

	i = 0;
	char **pre_token;
	(void)token;
	while (tab[i] != NULL)
	{
		j = 0;
		space_into_dot(&tab[i]);
		pre_token = ft_split(tab[i], '.');
		input_process2(pre_token, token);
		i++;
	}
	return (0);
}

int		parsing(char *line, t_token **token_list)
{
	int		i;
	char	**tab;
	t_token	*new;
	i = 0;
	// fonction de gestion d'erreurs
	tab = ft_split(line, ';');
	if (!tab)
		return (write_errors(3, NULL));
	//creation des elements
	while (i < tablen(tab))
	{
		token_add_back(token_list, &new);
		input_process(tab, &new);
		i++;
	}
	return(0);
}

int		main(/*int argc, char **argv, char **data*/)
{
	int ret;
	//int	fd;
	char *line;
	t_token *token;
	//t_token *begin;

	ret = 1;
	token = NULL;
	if (display_txt("banner.txt") == -1)
		return (-1);
	while(ret != 0)
	{
		write(1, "[minishell-1.0$ ", 16);
		get_next_input(&line);
		if (parsing(line, &token) == -1)
			return(-1);
		printf_all(token);
		//execution_commandes(envcopy)
		free_struct(&token);
		safe_free(&line);
	}
	safe_free(&line);
	safe_free((char **)&token);
	return (0);
}
