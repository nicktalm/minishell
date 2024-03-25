/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:04:24 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/25 18:24:12 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_execve(t_data *data, t_exe *cmd)
{
	check_for_bultin(data, cmd);
	data->path_exe = check_for_access(*data, cmd->argv);
	if (!(data->path_exe))
		error(ERROR_8);
	if (execve(data->path_exe, cmd->argv, data->cmd_path) == -1)
		error(ERROR_4);
}

void	check_for_bultin(t_data *data, t_exe *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])))
		exe_export(data, cmd);
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
	{
		exe_env(data->vars);
		exit (0);
	}
	else if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen(cmd->argv[0])))
	{
		exe_unset(data, cmd);
		exit (0);
	}
	else if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
	{
		exe_echo(cmd);
		exit (0);
	}
}

char	*check_for_access(t_data data, char **cmd)
{
	int		i;
	char	*newpath;
	char	*tmp;

	i = 0;
	if (ft_strchr(cmd[0], '/') && access(cmd[0], X_OK) != -1)
	{
		newpath = ft_strdup(cmd[0]);
		return (newpath);
	}
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
	int		fdd;

	fdd = 0;
	if (cmd->fd == 0)
	{
		fdd = open(cmd->f, cmd->mode);
		if (fdd < 0)
			error(cmd->f);
		else if (dup2(fdd, STDIN_FILENO) == -1)
			error(ERROR_3);
	}
	else
	{
		fdd = open(cmd->f, cmd->mode, 0644);
		if (fdd < 0)
			error(cmd->f);
		if (dup2(fdd, STDOUT_FILENO) == -1)
			error(ERROR_3);
	}
	if (!cmd->cmd)
		exit(0);
	execute_cmd(cmd->cmd, data);
}

// void	find_redir(t_cmd *cmd, int fdd, char *file, int *anw)
// {
// 	t_pipe		*cmd1;
// 	t_redir		*cmd2;

// 	cmd1 = NULL;
// 	cmd2 = NULL;
// 	if (cmd->type == EXECVE)
// 		return ;
// 	else if (cmd->type == PIPE)
// 	{
// 		cmd1 = (t_pipe *)cmd;
// 		find_redir(cmd1->left, fdd, file, anw);
// 		find_redir(cmd1->right, fdd, file, anw);
// 	}
// 	else if (cmd->type == REDIR)
// 	{
// 		cmd2 = (t_redir *)cmd;
// 		if (cmd2->fd == fdd && !ft_strncmp(cmd2->f, file, ft_strlen(cmd2->f)))
// 		{
// 			*anw = 1;
// 			return ;
// 		}
// 		else
// 			find_redir(cmd2->cmd, fdd, file, anw);
// 	}
// 	else if (cmd->type == HERE)
// 		return ;
// 	return ;
// }

void	exe_pipe(t_data *data, t_pipe *cmd)
{
	int		pfd[2];
	pid_t	id;

	id = 0;
	if (pipe(pfd) == -1)
		error(ERROR_5);
	first_cmd(pfd, id, cmd, data);
	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
		execute_cmd(cmd->right, data);
	if (id > 0)
	{
		waitpid(0, NULL, 0);
		close(pfd[0]);
		close(pfd[1]);
	}
	exit (0);
}

void	exe_here_doc(t_data *data, t_here_doc *cmd)
{
	int		fdd;
	char	*input;
	char	*quote_prompt;

	input = "";
	quote_prompt = "\001\e[1;33m\002> \001\e[0m\002";
	fdd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdd < 0)
		error("here_doc.txt");
	while (input)
	{
		input = readline(quote_prompt);
		if (!(ft_strncmp(input, cmd->l, ft_strlen(input) - 1)))
			break ;
		if ((ft_strchr(input, '$')))
			input = check_env(input, ft_strlen(input) - (ft_strlen(ft_strchr(input, '$')) - 1), *data);
		ft_putstr_fd(ft_strjoin(input, "\n"), fdd);
		free(input);
	}
	free(input);
	close(fdd);
	fdd = open("here_doc.txt", O_RDONLY);
	if (dup2(fdd, STDIN_FILENO) == -1)
		error("here\n");
	if (!cmd->cmd)
		exit(0);
	execute_cmd(cmd->cmd, data);
}

void	first_cmd(int *pfd, int id, t_pipe *cmd, t_data *data)
{
	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
	{
		close(pfd[0]);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			error(ERROR_3);
		execute_cmd(cmd->left, data);
	}
	if (id > 0)
	{
		waitpid(0, NULL, 0);
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			error(ERROR_3);
	}
}
