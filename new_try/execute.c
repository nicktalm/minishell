/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:04:24 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/11 14:36:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_execve(t_data *data, t_exe *cmd)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
		exe_execve_2(data, cmd);
	if (id > 0)
		waitpid(0, NULL, 0);
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
		printf("newpath = %s\n", newpath);
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

// void	exe_pipe(t_data *data, t_pipe *p)
// {
// 	pid_t	id;
// 	int		pfd[2];
// 	t_exe	*cmd;

// 	if (pipe(pfd) == -1)
// 		printf("error\n");
// 	id = fork();
// 	printf("id = %i\n", id);
// 	if (id < 0)
// 		printf("errro\n");
// 	if (id == 0)
// 	{
// 		close(pfd[0]);
// 		if (dup2(pfd[1], STDOUT_FILENO) == -1)
// 			printf("error\n");
// 		printf("here\n");
// 		cmd = (t_exe *)p->left;
// 		exe_execve_2(data, cmd);
// 	}
// 	waitpid(0, NULL, 0);
// 	id = fork();
// 	printf("id = %i\n", id);
// 	if (id < 0)
// 		printf("error\n");
// 	if (id == 0)
// 	{
// 		close(pfd[1]);
// 		if (dup2(pfd[0], STDIN_FILENO) == -1)
// 			printf("error\n");
// 		printf("here2\n");
// 		cmd = (t_exe *)p->right;
// 		exe_execve_2(data, cmd);
// 	}
// 	waitpid(0, NULL, 0);
// }

void	exe_execve_2(t_data *data, t_exe *cmd)
{
	char	*path;

	path = check_for_access(*data, cmd->argv);
	if (!(path))
	{
		error(ERROR_8);
		exit(0);
	}
	else
	{
		if (execve(path, cmd->argv, data->cmd_path) == -1)
		{
			error(ERROR_4);
			exit(0);
		}
	}
}

void	exe_pipe(t_data *data, t_pipe *p)
{
	int		pfd[2];
	int		i;
	t_exe	*cmd;
	t_exe	*cmd2;

	i = 0;
	cmd = (t_exe *)p->left;
	cmd2 = (t_exe *)p->right;
	if (pipe(pfd) == -1)
		printf("error\n");
	first_cmd_bonus(data, cmd, pfd);
	last_cmd(data, cmd2, pfd);
}

void	first_cmd_bonus(t_data *data, t_exe *cmd, int *pfd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		printf("error\n");
	if (pid == 0)
	{
		close(pfd[0]);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			printf("error\n");
		exe_execve_2(data, cmd);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			printf("error\n");
		//close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			printf("error\n");
	}
}

void	last_cmd(t_data *data, t_exe *cmd, int *pfd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		printf("error\n");
	if (pid == 0)
	{
		close(pfd[1]);
		exe_execve_2(data, cmd);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			printf("error\n");
		close(pfd[0]);
		close(pfd[1]);
	}
}
