/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:50:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/21 14:08:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <errno.h>
# include "./lib/libft/libft.h"

// struct

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*nxt;
}				t_var;

typedef struct s_data
{
	char			**cmd_path;
	struct s_cmd	*s_n;
	char			*in;
	struct s_var	*vars;
}				t_data;

typedef struct s_cmd
{
	int	type;
}				t_cmd;

typedef struct s_pipe
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_pipe;

typedef struct s_redir
{
	int				type;
	char			*f;
	int				mode;
	int				fd;
	struct s_cmd	*cmd;
}				t_redir;

typedef struct s_exe
{
	int		type;
	char	**argv;
}				t_exe;

typedef struct s_here_doc
{
	int				type;
	char			*l;
	struct s_cmd	*cmd;
}				t_here_doc;

void	init_env(char **env, t_var **vars);

// global varible

int		Signal;

// minishell

int		main(int argc, char **argv, char **env);
void	error(char *msg);
void	execute_cmd(t_cmd *t, t_data *data);

// cmd_prompt

char	*print_prompt(void);
char	*prompt_cwd(void);
int		find_s(char *pwd);
char	*free_used_string(char *f, char *s, int ff, int sf);

// quotes

char	*check_for_quotes(char *input);
void	double_or_single(int *d, int *s, char quote, int *first);
char	*wait_for_input(char quote, char *input);
char	*clean_input(char *input);
void	clean_input_2(char *input, int i, int *quote);

// quotes_2

char	*check_env_2(char *ret, char *input, int start, int end);
char	*check_env(char *input, int i);

// token

void	token(char *input, t_data *data);
char	get_token(char **s, char **q, char **eq);
int		check_next(char *s, char token);

// fill_struct

t_cmd	*fill_exe(char **q, char **eq, char *input, char **s);
t_cmd	*fill_pipe(t_cmd *l, t_cmd *r);
t_cmd	*fill_redir(char **s, char **q, char **eq, t_data *data);
t_cmd	*fill_here_doc(char **s, char **q, char **eq, t_data *data);
t_cmd	*search_next(t_cmd *cmd, int type);

// fill_struct_utils

char	**alloc_argv(char **s);
void	check_for_mode(t_redir **cmd, char **q);
char	**cat_struct_2(char **first, char **second, char **new);
void	cat_struct(t_cmd *f, t_cmd *s);
int		count_argvs(char **argv);

// execute

void	exe_execve(t_data *data, t_exe *cmd);
char	*check_for_access(t_data data, char **cmd);
void	exe_redir(t_data *data, t_redir *cmd);
// void	find_redir(t_cmd *cmd, int fd, char *file, int *anw);
void	exe_pipe(t_data *data, t_pipe *cmd);
void	first_cmd(int *pfd, int id, t_pipe *cmd, t_data *data);
void	exe_here_doc(t_data *data, t_here_doc *cmd);

// builtins

void	exe_cd(char *path);
void	exe_pwd(void);
void	exe_exit(void);
void	ctrl_c(int signal);
void	exe_env(t_var *vars);

// free

char	**freeup(char	**arr);

// struct nbr

# define EXECVE 0
# define PIPE 1
# define REDIR 2
# define HERE 3

// Error

# define ERROR_0 "Invalid number of arguments\n"
# define ERROR_1 "malloc"
# define ERROR_2 "open"
# define ERROR_3 "dup2"
# define ERROR_4 "execve"
# define ERROR_5 "pipe"
# define ERROR_6 "fork"
# define ERROR_7 "Env path not found !\n"
# define ERROR_8 "access"
# define ERROR_9 "wait"
# define ERROR_10 "Empty String\n"
# define ERROR_11 "pwd"
# define ERROR_12 "cd"

#endif