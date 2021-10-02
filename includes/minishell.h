/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:54:52 by alganoun          #+#    #+#             */
/*   Updated: 2021/10/02 22:47:39 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// il faut gérer les expansions dans le get_variable_value
// il faut gérer la bonne suppression des quotes dans le quote_remover

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1

# define BLUE '\001\e[1;34m\002'
# define GREEN '\001\033[32;1m\002'

# define BANNER			1
# define BAD_CHAR		1
# define WRONG_CMD		2
# define BAD_QUOTES		3
# define PATH_ERROR		4
# define REDIR_ERROR	5
# define VAR_NOT_FOUND	6
# define NOT_VALID_OPT	7
# define NOFILEORDIR	8
# define IS_DIRECTORY	9
# define PERM_DENIED	10
# define REDIR_ERROR2	11
# define BUFFER_SIZE	1024
# define EXIT_MSG	"\n[Process completed]"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../srcs/Utils/libft/Includes/libft.h"

# define ID_ECHO 0
# define ID_CD 1
# define ID_PWD 2
# define ID_EXPORT 3
# define ID_UNSET 4
# define ID_ENV 5
# define ID_BIN 6

# define TRUNC 1
# define APPEND 2
# define IN 3
# define INDEL 4
# define ERR 5
# define PIPE 6

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	int				cmd;
	pid_t			pid;
}				t_sig;

t_sig	g_sig;

typedef struct s_shell
{
	char			**env;
}					t_shell;

typedef struct s_token
{
	char			*cmd;
	char			**redir;
	char			**option;
	char			**arg;
	int				exp;
	char			*operator;
	struct s_token	*next;
	int				fd[2];
	char			type;
	int				std;
	char			in;
	char			out;
	int				ret;
	pid_t			pids[700];
	int				pid_index;
}					t_token;

/*------------UTILS---------------*/

void		get_next_input(char **line, char **env);
int			init_struct(t_token **token);
void		free_tab(char ***tab);
void		safe_free(char **str);
int			space_into_dot(char **str, char **env);
int			coma_into_dot(char **str);
int			tablen(char **tab);
int			reallocate_tab(char ***tab, char *str);
void		free_struct(t_token **token);
int			exit_free(t_token **token, char **line);
int			quote_remover(char **str);
char		*my_getenv(char *name, char **env);
int			variable_len(char *str);
char		**value_name_tab(char **env);
void		get_variable_value(char **str, char **env);
int			check_name(char *name);
void		token_cleaning(t_token **token);
int			simple_quote(char *str, int i);
int			double_quote(char *str, int i);
int			add_missing_space(char **str);
void		dquote_missing_space(char **str, char **tmp, int *i, int *j);
void		squote_missing_space(char **str, char **tmp, int *i, int *j);
void		dchev_missing_space(char **str, char **tmp, int *i, int *j);
void		pipechev_missing_space(char **str, char **tmp, int *i, int *j);
int			variable_existence(char *str, char **tab);
int			value_existence(char *str, char **tab);
char		**value_name_tab(char **env);
void		add_dollar(char ***tab);
void		print_sorted_tab(char **tab);
int			is_redir(char *str);
int			is_echo_option(char *str);
int			is_printable_quote(char *str, int i, char c);
void		printable_quote_cpy(char *str, char **tmp, int *i, int *j);
void		printable_quote_cpy2(char *str, char **tmp, int *i, int *j);
int			is_exportable(char *str);
void		free_env(t_shell **shell);
void		tild_replacer(char **str, char **env);
int			check_name(char *name);
int			is_exportable(char *str);
int			is_convertible(char *str, int index);
char		**export_name_tab(char **env);
int			is_forbiden_name2(char *str, int i, int only_assign);
int			is_forbiden_name(char *str);
int			equal_detection(char *str);
int			count_to_keep(char *str, char **env);
int			unset_is_forbiden_name(char *str);
void		free_replace(char **str, char **new);
int			count_to_copy(char *str, char *to_replace);
int			count_word(char *str, char *to_replace);

/*------------DISPLAY---------------*/
int			display_txt(char *str);
ssize_t		write_output(char *str);
int			write_errors(int option, char *str);
void		fd_write_errors(t_token *token);
int			write_exec_errors(void);

/*------------PARSING---------------*/
t_token		*token_last(t_token *token);
void		token_add_back(t_token **atoken, t_token **new);
t_token		*token_new(void);
int			option_finder(char *str, t_token **token);
int			pipe_finder(char *str, t_token **token);
int			redir_finder(char **tab, t_token **token);
void		arg_finder(char *str, t_token **token);
int			parsing(char **line, t_token **token_list, char **env);
int			input_process(char **line, t_token **token, char **env);
int			input_process2(char **pre_token, t_token **token, char **env);
int			token_filler(char *pre_token
			, t_token **token, char **env, int option);

/*------------BUILT-INS---------------*/
int			pwd_process(void);
int			echo_process(t_token *token);
int			export_process(t_token *token, char ***env);
int			unset_process(t_token *token, char ***env);
int			env_process(t_token *token, char **env);
void		cd_process(t_token *token, char ***env);
void		version_process(t_token *token);

/*------------EXECUTION---------------*/
int			run_process(t_token *token, t_shell **shell);
int			fork_process(t_token *token, t_shell **shell, int fdd);
void		execution(t_token *token, t_shell **shell, int pipe);
char		**strenv(char *s, char **env);
void		exec_cmd(t_token *token, t_shell **shell);
void		exec_cmd_fork(t_token *token, t_shell **shell);
void		choose(t_token *token, t_shell **shell, int pipe);
void		redirection(t_token *token, t_shell **shell, int pipe);
int			set_type(char *redir);
int			count_redir(char **redir);
void		status_child(void);
void		status_child(void);
char		*build_line(char **tab, char *line);
char		**build_cmd(t_token *token);
char		**bin(t_shell **shell, char *cmd);
void		skip_bin(t_token *token);

/*------------SIGNAL&EXIT---------------*/
void		exit_cmd(t_token *token);
void		exit_prog(t_token **token, char *exit_message, int status);
void		sig_int(int code);
void		sig_quit(int code);
void		sig_init(void);
void		sigint(int sig);

#endif
