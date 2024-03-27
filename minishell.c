/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/27 12:42:36 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	id;

	data.vars = NULL;
	data.export = NULL;
	data.path_exe = NULL;
	if (argc == 1)
	{
		data.cmd_path = ft_split(getenv("PATH"), ':');
		init_env(env, &data.vars);
		init_env(env, &data.export);
		// sort_export(&data.export);
		while (1)
		{
			data.in = print_prompt();
			data.in = check_for_quotes(data.in, data);
			if (ft_strcmp(data.in, ""))
			{
				token(data.in, &data);
				if (!ka(&data))
				{
					id = fork();
					if (id < 0)
						error(ERROR_6);
					else if (id == 0)
						execute_cmd(data.s_n, &data);
					else if (id > 0)
					{
						waitpid(0, NULL, 0);
						unlink("here_doc.txt");
					}
				}
				free(data.in);
			}
		}
	}
	else
		error(argv[1]);
	return (0);
}

int	ka(t_data *data)
{
	t_exe	*cmd;

	if (data->s_n->type == EXECVE)
	{
		cmd = (t_exe *)data->s_n;
		if (!ft_strcmp(cmd->argv[0], "export"))
		{
			exe_export_env(data, cmd);
			exe_export_export(data, cmd);
		}
		else if (!ft_strcmp(cmd->argv[0], "exit"))
			exe_exit(*data);
		else if (!ft_strcmp(cmd->argv[0], "unset"))
			exe_unset(data, cmd);
		else if (!ft_strcmp(cmd->argv[0], "cd"))
			exe_cd(data, cmd);
		else
			return (0);
		return (1);
	}
	return (0);
}

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

void	execute_cmd(t_cmd *t, t_data *data)
{
	t_exe		*cmd;
	t_pipe		*cmd1;
	t_redir		*cmd2;
	t_here_doc	*cmd3;

	cmd = NULL;
	cmd1 = NULL;
	cmd2 = NULL;
	cmd3 = NULL;
	if (t->type == EXECVE)
	{
		// fprintf(stderr, "exe\n");
		cmd = (t_exe *)t;
		exe_execve(data, cmd);
		//exit(0);
	}
	else if (t->type == PIPE)
	{
		// fprintf(stderr, "pipe\n");
		cmd1 = (t_pipe *)t;
		exe_pipe(data, cmd1);
	}
	else if (t->type == REDIR)
	{
		cmd2 = (t_redir *)t;
		// fprintf(stderr, "redir %i %s\n", cmd2->fd, cmd2->f);
		exe_redir(data, cmd2);
	}
	else if (t->type == HERE)
	{
		// fprintf(stderr, "here\n");
		cmd3 = (t_here_doc *)t;
		exe_here_doc(data, cmd3);
	}
}
