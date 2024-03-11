/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:38:51 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/11 13:11:26 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_pipe(t_data data)
{
	if (data.here_doc > 0 || data.input > 0
		|| data.inputop > 0 || data.outendop > 0)
		open_in_and_outfile_bonus(&data);
	// search_env_path(envp, &data);
	// parsing_paths(envp[data.path_nbr], &data);
	execute_cmds_bonus(data);
	//freeall(data);
	return (0);
}

void	exe_pipe(t_data *data, t_pipe *p)
{
	int		pfd[2];
	int		i;
	t_exe	*cmd;
	t_exe	*cmd2;

	i = 0;
	cmd = (t_exe *)p.left;
	cmd2 = (t_exe *)p.right;
	if (pipe(pfd) == -1)
		printf("error\n");
	first_cmd_bonus(data, cmd.argv, pfd, data->cmd_path);
	// i++;
	// while (data.cmd[i + 1])
	// {
	// 	next_cmd(data, data.cmd[i], envp);
	// 	i++;
	// }
	last_cmd(data, cmd.argv, pfd, data->cmd_path);
}

void	first_cmd_bonus(t_data *data, char **cmd, int *pfd, char **envp)
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

// void	next_cmd(t_data data, char **cmd, char **envp)
// {
// 	int	pid;
// 	int	status;
// 	int	pfd2[2];

// 	if (pipe(pfd2) == -1)
// 		error(ERROR_5, data);
// 	pid = fork();
// 	if (pid == -1)
// 		error(ERROR_6, data);
// 	if (pid == 0)
// 	{
// 		close(pfd2[0]);
// 		if (dup2(pfd2[1], STDOUT_FILENO) == -1)
// 			error(ERROR_3, data);
// 		child_process(data, cmd, envp);
// 	}
// 	else
// 	{
// 		if (waitpid(0, &status, 0) == -1)
// 			error(ERROR_9, data);
// 		close(pfd2[1]);
// 		if (dup2(pfd2[0], STDIN_FILENO) == -1)
// 			error(ERROR_3, data);
// 	}
// }

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

void	open_in_and_outfile_bonus(t_data *data)
{
	char	*result;

	if (data->inputop > 0)
	{
		result = search_file(data->input, '<');
		if (!result)
			data->infile = STDIN_FILENO;
		else
			data->infile = open(result, O_RDONLY);
		if (data->infile == -1)
			error(ERROR_2);
	}
	if (data->here_doc > 0)
		create_here_doc_file(data);
	if (data->outputop > 0)
	{
		result = search_file(data->input, '>');
		if (!result)
			data->infile = STDOUT_FILENO;
		else
			data->infile = open(result, O_RDONLY);
		if (data->infile == -1)
			error(ERROR_2);
	}
	if (data->outendop > 0)
		
}

char	*search_file(char **input, char op)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == op)
		{
			if (op == '<<')
				return (input[i + 1]);
			else if (!access(input[i - 1], R_OK))
				return (input[i - 1]);
			else if (!access(input[i + 1], R_OK))
				return (input[i + 1]);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
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

void	create_here_doc_file(t_data *data)
{
	int		file;
	char	*str;
	char	*tmp;

	str = "";
	file = open("here_doc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file == -1)
		error(ERROR_2);
	tmp = ft_strjoin(search_file(data->input, '<<'), "\n");
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
		error(ERROR_2);
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
