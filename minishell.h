/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:50:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/27 11:24:47 by lbohm            ###   ########.fr       */
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
	char			**input;
	char			**cmdpath;
	int				pipe;
	int				inputop;
	int				infile;
	int				outfile;
	int				outputop;
	int				here_doc;
	int				outendop;
	struct s_tree	**tree;
	struct s_leaf	**leaf;
}				t_data;

typedef struct s_tree
{
	char	*opl;
	void	*left;
	char	*opr;
	void	*right;
}				t_tree;

typedef struct s_leaf
{
	char	*input1;
	char	*input2;
}				t_leaf;

// minishell

void	execmd(t_data data);
char	*check_for_access(t_data data, char **cmd);
void	exe_other(t_data data);
void	error(char *msg);
void	exe_pwd(void);
void	exe_cd(t_data data);
void	check_for_operator(t_data *data);
void	ctrl_c(int signal);
void	exe_exit(void);

// split_with_quotes

char	**split_with_q(char const *s, char c);
int		how_many_words(char const *s, char c);
char	*wordlen(char const *s, char c, int *p);
char	**freeup(char	**arr);
char	*quotes(char *s, int *p, char quot);

// parsing

void	parsing(char *input);
void	recursive_parsing(char **argv, int i, int t, int l, t_data *data);
int		count_strs(char **argv);
void	allocate_structs(char **argv, t_data *data);
int		count_trees(char **argv);
void	add_to_struct(char **argv, t_data *data, int i, int t, int l, char *op);

// cmd_promt

char	*print_promt(void);
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