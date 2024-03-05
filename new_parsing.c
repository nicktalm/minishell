/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:55:58 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/05 12:51:30 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_argv(char **argv);
int		check_for_token(char *argv);

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
	printf("count = %i\n", count);
	data->argv = (char ***)malloc ((count + 1) * sizeof(char **));
	if (!data->argv)
		printf("error argv\n");
	data->argv[count] = NULL;
	while (argv[i])
	{
		printf("argv[%i] = %s\n", i, argv[i]);
		i++;
	}
	i = 0;
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
			while (argv[i])
			{
				if (check_for_token(argv[i]))
					i++;
				else
					break ;
			}
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

int	main(void)
{
	char	*cmd;
	t_data	data;

	cmd = "cat > ls -la";
	parsing(cmd, &data);
	int	i = 0;
	int	j = 0;
	while (data.argv[i])
	{
		j = 0;
		while (data.argv[i][j])
		{
			printf("data.argv[%i][%i] = %s\n", i, j, data.argv[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}
