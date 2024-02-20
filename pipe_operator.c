/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:38:51 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/20 10:43:55 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_pipe(int argc, char **argv, char **envp)
{
	t_data	data;

	data.files = NULL;
	data.cmd = NULL;
	data.path = NULL;
	open_in_and_outfile_bonus(argc, argv, &data);
	search_env_path(envp, &data);
	parsing_paths(envp[data.path_nbr], &data);
	execute_cmds_bonus(data, envp);
	freeall(data);
	return (0);
}

void	execute_cmds_bonus(t_data data, char **envp)
{
	int	pfd[2];
	int	i;

	i = 0;
	if (pipe(pfd) == -1)
		error(ERROR_5, data);
	first_cmd_bonus(data, data.cmd[i], pfd, envp);
	i++;
	while (data.cmd[i + 1])
	{
		next_cmd(data, data.cmd[i], envp);
		i++;
	}
	last_cmd(data, data.cmd[i], pfd, envp);
}

void	first_cmd_bonus(t_data data, char **cmd, int *pfd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd[0]);
		if (dup2(data.infile, STDIN_FILENO) == -1)
			error(ERROR_3, data);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, cmd, envp);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			error(ERROR_3, data);
	}
}

void	next_cmd(t_data data, char **cmd, char **envp)
{
	int	pid;
	int	status;
	int	pfd2[2];

	if (pipe(pfd2) == -1)
		error(ERROR_5, data);
	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd2[0]);
		if (dup2(pfd2[1], STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, cmd, envp);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
		close(pfd2[1]);
		if (dup2(pfd2[0], STDIN_FILENO) == -1)
			error(ERROR_3, data);
	}
}

void	last_cmd(t_data data, char **cmd, int *pfd, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd[1]);
		if (dup2(data.outfile, STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, cmd, envp);
	}
	else
	{
		close(data.infile);
		close(data.outfile);
		close(pfd[0]);
		close(pfd[1]);
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
		unlink("here_doc.txt");
	}
}

void	open_in_and_outfile_bonus(int argc, char **argv, t_data *data)
{
	if (argc > 4)
	{
		if (ft_strncmp(argv[1], "here_doc", 8))
		{
			parsing_bonus(argc, argv, data);
			check_for_empty_str(argc, argv, *data);
			data->infile = open(data->files[0], O_RDONLY);
			if (data->infile == -1)
				error(ERROR_2, *data);
		}
		else
		{
			create_here_doc_file(argc, argv, data);
			check_for_empty_str(argc, argv, *data);
		}
		data->outfile = open(data->files[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->outfile == -1)
			error(ERROR_2, *data);
	}
	else
		error(ERROR_0, *data);
}

void	parsing_bonus(int argc, char **argv, t_data *data)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	if (argc > 4)
	{
		allocat_struct(argc, data, 2);
		while (i < argc)
		{
			if (i == 1)
				data->files[0] = argv[i];
			else if (i + 1 == argc)
				data->files[1] = argv[i];
			else
			{
				data->cmd[pos] = ft_split(argv[i], ' ');
				pos++;
			}
			i++;
		}
	}
	else
		error(ERROR_0, *data);
}

void	create_here_doc_file(int argc, char **argv, t_data *data)
{
	int		file;
	char	*str;
	char	*tmp;

	str = "";
	parsing_here_doc(argc, argv, data);
	file = open("here_doc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file == -1)
		error(ERROR_2, *data);
	tmp = ft_strjoin(data->files[0], "\n");
	while (str)
	{
		str = get_next_line(0);
		if (!(ft_strncmp(str, tmp, ft_strlen(str))))
			break ;
		ft_putstr_fd(str, file);
		free(str);
	}
	free(str);
	free(tmp);
	close(file);
	data->infile = open("here_doc.txt", O_RDONLY);
	if (data->infile == -1)
		error(ERROR_2, *data);
}

void	parsing_here_doc(int argc, char **argv, t_data *data)
{
	int	i;
	int	pos;

	i = 2;
	pos = 0;
	if (argc > 5)
	{
		allocat_struct(argc, data, 3);
		while (argv[i])
		{
			if (i == 2)
				data->files[0] = argv[i];
			else if (i + 1 == argc)
				data->files[1] = argv[i];
			else
			{
				data->cmd[pos] = ft_split(argv[i], ' ');
				pos++;
			}
			i++;
		}
	}
	else
		error(ERROR_0, *data);
}

void	search_env_path(char **env, t_data *data)
{
	int	i;

	i = 0;
	data->path_nbr = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			data->path_nbr = i;
			break ;
		}
		i++;
	}
	if (!(env[i]))
		error(ERROR_7, *data);
}

void	parsing_paths(char *env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i] != '/')
		i++;
	data->path = ft_split(env + i, ':');
}

void	freearr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	child_process(t_data data, char **cmd, char **envp)
{
	char	*path;

	path = check_for_access(data, cmd);
	if (!(path))
		error(ERROR_8, data);
	else
		if (execve(path, cmd, envp) == -1)
			error(ERROR_4, data);
}
