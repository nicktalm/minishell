/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/21 14:08:43 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	id;

	argc = 0;
	argv = 0;
	data.vars = NULL;
	data.cmd_path = ft_split(getenv("PATH"), ':');
	init_env(env, &data.vars);
	exe_env(data.vars);
	while (1)
	{
		data.in = print_prompt();
		data.in = check_for_quotes(data.in);
		if (ft_strncmp(data.in, "", ft_strlen(data.in)))
		{
			token(data.in, &data);
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
			free(data.in);
		}
	}
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
		//printf("exe\n");
		cmd = (t_exe *)t;
		if (cmd)
			exe_execve(data, cmd);
	}
	else if (t->type == PIPE)
	{
		//printf("pipe\n");
		cmd1 = (t_pipe *)t;
		exe_pipe(data, cmd1);
	}
	else if (t->type == REDIR)
	{
		cmd2 = (t_redir *)t;
		//printf("redir %i\n", cmd2->fd);
		exe_redir(data, cmd2);
	}
	else if (t->type == HERE)
	{
		//printf("here\n");
		cmd3 = (t_here_doc *)t;
		exe_here_doc(data, cmd3);
	}
}
