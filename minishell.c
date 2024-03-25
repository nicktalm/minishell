/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/25 18:37:31 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	id;

	data.vars = NULL;
	data.path_exe = NULL;
	if (argc == 1)
	{
		init_env(env, &data.vars);
		data.cmd_path = ft_split(get_env("PATH", &data.vars), ':');
		while (1)
		{
			data.in = print_prompt();
			data.in = check_for_quotes(data.in, data);
			if (ft_strcmp(data.in, ""))
			{
				token(data.in, &data);
				if (!ka(data))
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

int	ka(t_data data)
{
	t_exe	*cmd;

	if (data.s_n->type == EXECVE)
	{
		cmd = (t_exe *)data.s_n;
		if (!ft_strcmp(cmd->argv[0], "export"))
			exe_export(&data, cmd);
		else if (!ft_strcmp(cmd->argv[0], "exit"))
			exe_exit(data);
		else if (!ft_strcmp(cmd->argv[0], "unset"))
			exe_unset(&data, cmd);
		else if (!ft_strcmp(cmd->argv[0], "cd"))
			exe_cd(cmd->argv[1]);
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
	if (t->type == EXECVE)
		exe_execve(data, (t_exe *)t);
	else if (t->type == PIPE)
		exe_pipe(data, (t_pipe *)t);
	else if (t->type == REDIR)
		exe_redir(data, (t_redir *)t);
	else if (t->type == HERE)
		exe_here_doc(data, (t_here_doc *)t);
}
