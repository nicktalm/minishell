/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:55:58 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/05 18:23:37 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, t_data *data)
{
	char	**argv;
	char	**new;
	int		i;
	int		a;
	int		start;
	int		count;

	i = 0;
	a = 0;
	start = i;
	argv = split_with_q(input, ' ');
	count = count_argv(argv);
	data->argv = (char ***)malloc ((count + 1) * sizeof(char **));
	if (!data->argv)
		printf("error argv\n");
	data->argv[count] = NULL;
	while (argv[i])
	{
		if (!check_for_token(argv[i]))
		{
			data->argv[a] = split_with_q(argv[i], ' ');
			a++;
			i++;
		}
		else
		{
			start = i;
			if (!check_for_cmd(data, argv[i]))
			{
				while (argv[i])
				{
					if (check_for_token(argv[i]))
						i++;
					else
						break ;
				}
			}
			else
				i++;
			new = (char **)malloc ((i - (start - 1)) * sizeof(char *));
			if (!new)
				printf("error new\n");
			new[i - start] = NULL;
			count = 0;
			while (start < i)
			{
				new[count] = ft_strdup(argv[start]);
				count++;
				start++;
			}
			data->argv[a] = new;
			a++;
		}
	}
}

int	check_for_token(char *argv)
{
	if (!ft_strncmp(argv, "|", ft_strlen(argv))
		|| !ft_strncmp(argv, "<", ft_strlen(argv))
		|| !ft_strncmp(argv, ">", ft_strlen(argv))
		|| !ft_strncmp(argv, "<<", ft_strlen(argv))
		|| !ft_strncmp(argv, ">>", ft_strlen(argv)))
		return (0);
	else if (access(argv, F_OK | R_OK) != -1)
		return (0);
	return (1);
}

int	check_for_cmd(t_data *data, char *argv)
{
	int		i;
	char	*cmd;
	char	*tmp;

	i = 0;
	while (data->cmdpath[i])
	{
		tmp = ft_strjoin(data->cmdpath[i], "/");
		cmd = ft_strjoin(tmp, argv);
		free(tmp);
		if (access(cmd, F_OK | X_OK) != -1)
		{
			free(cmd);
			return (0);
		}
		free(cmd);
		i++;
	}
	return (1);
}

int	count_argv(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
			count += 2;
		i++;
	}
	return (count + 1);
}

// int	main(void)
// {
// 	char	*cmd;
// 	t_data	data;
// 	char	*path;

// 	cmd = "< infile cat | ls -la | wc -w > outfile";
// 	path = getenv("PATH");
// 	data.cmdpath = ft_split(path, ':');
// 	parsing(cmd, &data);
// 	int	i = 0;
// 	int	j = 0;
// 	while (data.argv[i])
// 	{
// 		j = 0;
// 		while (data.argv[i][j])
// 		{
// 			printf("data.argv[%i][%i] = %s\n", i, j, data.argv[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
