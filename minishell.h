/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:50:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/29 14:00:37 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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
	char			***argv;
	char			**cmdpath;
	struct s_tree	**tree;
	struct s_leaf	**leaf;
	int				fd;
	int				save_fd;
	char			*op;
}				t_data;

typedef struct s_tree
{
	char	*op;
	void	*left;
	void	*right;
}				t_tree;

typedef struct s_leaf
{
	char	**input1;
	char	**input2;
}				t_leaf;

// minishell

void	execmd(t_data data);
char	*check_for_access(t_data data, char **cmd);
void	exe_other(t_data *data, t_leaf *tree);
void	error(char *msg);
void	exe_pwd(void);
void	exe_cd(char *path);
//void	check_for_operator(t_data *data);
void	ctrl_c(int signal);
void	exe_exit(void);
char	**sort_argv(char *input);
char	***tripple(char **newinput);

// split_with_quotes

char	**split_with_q(char const *s, char c);
int		how_many_words(char const *s, char c);
char	*wordlen(char const *s, char c, int *p);
char	**freeup(char	**arr);
char	*quotes(char *s, int *p, char quot);

// parsing

void	parsing(t_data data);
void	recursive_parsing(int i, int t, int l, t_data *d);
int		count_strs(char ***argv);
void	allocate_structs(t_data *data);
int		count_trees(char ***argv);
void	add_to_struct(int i, int t, int l, t_data *data);
void	exe_cmd(void *tree, int i, t_data *data);
void	exe_redir(t_tree *tree, t_data *data);

// cmd_promt

char	*print_prompt(void);
char	*promt_cwd(void);
int		find_s(char *pwd);


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