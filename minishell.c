/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:23:40 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/19 17:50:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*input;
	int		i;
	char	*path;

	path = getenv("PATH");
	data.cmdpath = ft_split(path, ':');
	while (1)
	{
		i = 0;
		input = readline("\033[1;34mminishell > \033[0m");
		data.input = ft_split(input, ' ');
		while (data.input[i])
		{
			if (!ft_strncmp(data.input[i], "|", ft_strlen("|")))
			{
				printf("pipex\n");
				break ;
			}
			else if (!ft_strncmp(data.input[i], "<<", ft_strlen("<<")) || !ft_strncmp(data.input[i], ">>", ft_strlen(">>")))
			{
				printf("<< or >> \n");
				break ;
			}
			else if (!ft_strncmp(data.input[i], "<", ft_strlen("<")) || !ft_strncmp(data.input[i], ">", ft_strlen(">")))
			{
				printf("< or > \n");
				break ;
			}
			i++;
		}
		if (!data.input[i])
			execmd(data);
		free(input);
	}
	return (0);
}

void	execmd(t_data data)
{
	if (!ft_strncmp(data.input[0], "echo", ft_strlen("echo")))
	{
		printf("echo\n");
		//exe_echo();
	}
	else if (!ft_strncmp(data.input[0], "cd", ft_strlen("cd")))
	{
		printf("cd\n");
		//exe_cd();
	}
	else if (!ft_strncmp(data.input[0], "pwd", ft_strlen("pwd")))
	{
		printf("pwd\n");
		//exe_pwd();
	}
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
	{
		printf("exit\n");
		//exe_exit();
	}
	else
	{
		printf("other\n");
		exe_other(data);
	}
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
			error(ERROR_8);
		else
		{
			if (execve(path, data.input, data.cmdpath) == -1)
				error(ERROR_4);
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
