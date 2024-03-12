/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:50:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/12 11:18:05 by lbohm            ###   ########.fr       */
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

typedef struct s_data
{
	char			**cmd_path;
	struct s_cmd	*start_node;
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
	char			*file;
	int				mode;
	int				fd;
	struct s_cmd	*cmd;
}				t_redir;

typedef struct s_exe
{
	int		type;
	char	**argv;
}				t_exe;

// minishell

int		main(void);
void	error(char *msg);
void	exe_other(t_data *data, t_cmd *cmd);
char	*check_for_access(t_data data, char **cmd);

// split_with_quotes

char	**split_with_q(char const *s, char c);
int		how_many_words(char const *s, char c);
char	*wordlen(char const *s, char c, int *p);
char	**freeup(char	**arr);
char	*quotes(char *s, int *p, char quot);

// cmd_promt

char	*print_prompt(void);
char	*promt_cwd(void);
int		find_s(char *pwd);

// quotes

char	*check_for_quotes(char *input);
void	double_or_single(int *d, int *s, char quote, int *first);
char	*wait_for_input(char quote, char *input);

// token

void	token(char *input, t_data *data);
char	get_token(char **s, char **q, char **eq);
int		check_next(char *s, char token);

// fill_struct

t_cmd	*fill_exe(char **q, char **eq, char *input, char **s);
t_cmd	*fill_pipe(t_cmd *l, t_cmd *r);
t_cmd	*fill_redir(char **s, char **q, char **eq, t_cmd *c, char *input);
char	**alloc_argv(char **s);
void	check_for_mode(t_redir **cmd, char **q);

// execute

void	exe_execve(t_data *data, t_exe *cmd);
char	*check_for_access(t_data data, char **cmd);
void	exe_pipe(t_data *data, t_pipe *p);
void	exe_execve_2(t_data *data, t_exe *cmd);
void	first_cmd_bonus(t_data *data, t_exe *cmd, int *pfd);
void	last_cmd(t_data *data, t_exe *cmd, int *pfd);

// test

void	test(t_cmd *t);

// struct nbr

# define EXECVE 0
# define PIPE 1
# define REDIR 2

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