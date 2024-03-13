/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:04:24 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/13 11:52:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_execve(t_data *data, t_exe *cmd)
{
	char	*path;

	path = check_for_access(*data, cmd->argv);
	if (!(path))
		error(ERROR_8);
	else
	{
		if (execve(path, cmd->argv, data->cmd_path) == -1)
			error(ERROR_4);
	}
}

char	*check_for_access(t_data data, char **cmd)
{
	int		i;
	char	*newpath;
	char	*tmp;

	i = 0;
	while (data.cmd_path[i])
	{
		tmp = ft_strjoin(data.cmd_path[i], "/");
		newpath = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(newpath, X_OK) == -1)
		{
			i++;
			free(newpath);
		}
		else
			return (newpath);
	}
	return (NULL);
}

void	exe_redir(t_data *data, t_redir *cmd)
{
	int	fdd;

	if (cmd->fd == 0)
	{
		fdd = open(cmd->file, cmd->mode);
		if (fdd < 0)
			error(ERROR_2);
		else if (dup2(fdd, STDIN_FILENO) == -1)
			error(ERROR_3);
	}
	else
	{
		fdd = open(cmd->file, cmd->mode, 0644);
		if (dup2(fdd, STDOUT_FILENO) == -1)
			error(ERROR_3);
	}
	test(cmd->cmd, data);
}

void	exe_pipe(t_data *data, t_pipe *cmd)
{
	int		pfd[2];
	pid_t	id;

	if (pipe(pfd) == -1)
		error(ERROR_5);
	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
	{
		close(pfd[0]);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			error(ERROR_3);
		test(cmd->left, data);
	}
	if (id > 0)
	{
		waitpid(0, NULL, 0);
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			error(ERROR_3);
	}
	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
	{
		test(cmd->right, data);
	}
	if (id > 0)
	{
		waitpid(0, NULL, 0);
		close(pfd[0]);
		close(pfd[1]);
	}
	exit (0);
}
