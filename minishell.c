/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:23:40 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/27 11:25:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*input;
	char	*path;

	path = getenv("PATH");
	data.cmdpath = ft_split(path, ':');
	data.pipe = 0;
	data.inputop = 0;
	data.outputop = 0;
	data.here_doc = 0;
	data.outendop = 0;
	signal(SIGINT, ctrl_c);
	while (1)
	{
		input = print_promt();
		//parsing(input);
		data.input = split_with_q(input, ' ');
		check_for_operator(&data);
		freeup(data.input);
		free(input);
	}
	return (0);
}

void	check_for_operator(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (!ft_strncmp(data->input[i], "|", ft_strlen("|")))
			data->pipe++;
		else if (!ft_strncmp(data->input[i], "<<", ft_strlen("<<")))
			data->here_doc++;
		else if (!ft_strncmp(data->input[i], ">>", ft_strlen(">>")))
			data->outendop++;
		else if (!ft_strncmp(data->input[i], "<", ft_strlen("<")))
			data->inputop++;
		else if (!ft_strncmp(data->input[i], ">", ft_strlen(">")))
			data->outputop++;
		i++;
	}
	if (!data->input[i])
		execmd(*data);
}

void	execmd(t_data data)
{
	if (!ft_strncmp(data.input[0], "echo", ft_strlen("echo")))
	{
		printf("echo\n");
		//exe_echo();
	}
	else if (!ft_strncmp(data.input[0], "cd", ft_strlen("cd")))
		exe_cd(data);
	else if (!ft_strncmp(data.input[0], "pwd", ft_strlen("pwd")))
		exe_pwd();
	else if (!ft_strncmp(data.input[0], "export", ft_strlen("export")))
	{
		printf("export\n");
		//exe_export();
	}
	else if (!ft_strncmp(data.input[0], "unset", ft_strlen("unset")))
	{
		printf("unset\n");
		//exe_unset();
	}
	else if (!ft_strncmp(data.input[0], "env", ft_strlen("env")))
	{
		printf("env\n");
		//exe_env();
	}
	else if (!ft_strncmp(data.input[0], "exit", ft_strlen("exit")))
		exe_exit();
	if (!ft_strncmp(data.input[0], "clear", ft_strlen("clear")))
		printf("%s\n", tgetstr("clear", NULL));
	else
		exe_other(data);
}

void	exe_cd(t_data data)
{
	if (chdir(data.input[1]))
		error(ERROR_12);
}

void	exe_pwd(void)
{
	char	*cwd;
	int		size;

	size = 1;
	cwd = malloc(size * sizeof(char));
	if (!cwd)
		error(ERROR_1);
	while (getcwd(cwd, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size++;
			free(cwd);
			cwd = malloc(size * sizeof(char));
			if (!cwd)
				error(ERROR_1);
		}
		else
			error(ERROR_11);
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	exe_exit(void)
{
	// alles free, was allokiert wird
	exit(0);
}

void	ctrl_c(int signal)
{
	signal = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exe_other(t_data data)
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
	{
		path = check_for_access(data, data.input);
		if (!(path))
		{
			error(ERROR_8);
			exit(0);
		}
		else
		{
			if (execve(path, data.input, data.cmdpath) == -1)
			{
				error(ERROR_4);
				exit(0);
			}
		}
	}
	if (id > 0)
	{
		waitpid(0, NULL, 0);
	}
}

char	*check_for_access(t_data data, char **cmd)
{
	int		i;
	char	*newpath;
	char	*tmp;

	i = 0;
	while (data.cmdpath[i])
	{
		tmp = ft_strjoin(data.cmdpath[i], "/");
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

void	error(char *msg)
{
	perror(msg);
}
