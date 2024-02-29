/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:23:40 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/29 14:03:36 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*input;
	char	*path;
	char	**newinput;

	path = getenv("PATH");
	data.cmdpath = ft_split(path, ':');
	signal(SIGINT, ctrl_c);
	while (1)
	{
		input = print_prompt();
		newinput = sort_argv(input);
		data.argv = tripple(newinput);
		parsing(data);
		//exit(0);
		//check_for_operator(&data);
		//freeup(data.argv);
		//free(input);
	}
	return (0);
}

char	**sort_argv(char *input)
{
	int		i;
	int		end;
	int		start;
	int		count;
	char	**newinput;

	i = 0;
	start = 0;
	end = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<'
			|| input[i] == '>' || (input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
			count += 2;
		i++;
	}
	count++;
	newinput = (char **)malloc ((count + 1) * sizeof(char *));
	if (!newinput)
		printf("error\n");
	newinput[count] = NULL;
	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<'
			|| input[i] == '>' || (input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
		{
			end = i;
			printf("i = %i\n", i);
			newinput[count] = ft_substr(input, start, end - start);
			count++;
			if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<')
				|| (input[i] == '>' && input[i + 1] != '>'))
			{
				if (input[i] == '|')
					newinput[count] = ft_strdup("|");
				else if (input[i] == '<')
					newinput[count] = ft_strdup("<");
				else
					newinput[count] = ft_strdup(">");
			}
			else
			{
				if (input[i] == '<')
					newinput[count] = ft_strdup("<<");
				else
					newinput[count] = ft_strdup(">>");
			}
			count++;
			start = end + 1;
		}
		i++;
	}
	end = i;
	if (!input[i])
		newinput[count] = ft_substr(input, start, end - start);
	free(input);
	return (newinput);
}

char	***tripple(char **newinput)
{
	char	***tripple;
	int		i;

	i = 0;
	while (newinput[i])
		i++;
	tripple = (char ***)malloc ((i + 1) * sizeof(char **));
	if (!tripple)
		printf("error\n");
	tripple[i] = NULL;
	i = 0;
	while (newinput[i])
	{
		tripple[i] = split_with_q(newinput[i], ' ');
		free(newinput[i]);
		i++;
	}
	free(newinput);
	return (tripple);
}

// void	execmd(t_data data)
// {
// 	if (!ft_strncmp(data.argv[0], "echo", ft_strlen("echo")))
// 	{
// 		printf("echo\n");
// 		exe_echo();
// 	}
// 	else if (!ft_strncmp(data.argv[0], "cd", ft_strlen("cd")))
// 		exe_cd(data);
// 	else if (!ft_strncmp(data.argv[0], "pwd", ft_strlen("pwd")))
// 		exe_pwd();
// 	else if (!ft_strncmp(data.argv[0], "export", ft_strlen("export")))
// 	{
// 		printf("export\n");
// 		exe_export();
// 	}
// 	else if (!ft_strncmp(data.argv[0], "unset", ft_strlen("unset")))
// 	{
// 		printf("unset\n");
// 		exe_unset();
// 	}
// 	else if (!ft_strncmp(data.argv[0], "env", ft_strlen("env")))
// 	{
// 		printf("env\n");
// 		exe_env();
// 	}
// 	else if (!ft_strncmp(data.argv[0], "exit", ft_strlen("exit")))
// 		exe_exit();
// 	else if (!ft_strncmp(data.argv[0], "clear", ft_strlen("clear")))
// 		printf("%s\n", tgetstr("clear", NULL));
// 	else
// 		exe_other(data);
// }

void	exe_cd(char *path)
{
	if (chdir(path))
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

void	exe_other(t_data *data, t_leaf *tree)
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
	{
		path = check_for_access(*data, tree->input1);
		if (!(path))
		{
			error(ERROR_8);
			exit(0);
		}
		else
		{
			if (execve(path, tree->input1, data->cmdpath) == -1)
			{
				error(ERROR_4);
				exit(0);
			}
		}
	}
	if (id > 0)
	{
		waitpid(0, NULL, 0);
		if (data->op)
		{
			if (!ft_strncmp(data->op, ">", ft_strlen(data->op)))
			{
				close(data->fd);
				if (dup2(data->save_fd, STDOUT_FILENO) == -1)
					printf("dup2 error\n");
			}
			else if (!ft_strncmp(data->op, "<", ft_strlen(data->op)))
			{
				close(data->fd);
				if (dup2(data->save_fd, STDIN_FILENO) == -1)
					printf("dup2 error\n");
			}
		}
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
