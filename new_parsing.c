/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:55:58 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/08 11:14:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	parsing(char *input, t_data *data)
// {
// 	char	**new_input;
// 	char	**new;
// 	int		i;
// 	int		a;
// 	int		start;
// 	int		count;

// 	i = 0;
// 	a = 0;
// 	start = i;
// 	new_input = split_with_q(input, ' ');
// 	free(input);
// 	count = count_argv(new_input);
// 	data->argv = (char ***)malloc ((count + 1) * sizeof(char **));
// 	if (!data->argv)
// 		printf("error argv\n");
// 	printf("parsing count = %i\n", count);
// 	return ;
// 	data->argv[count] = NULL;
// 	while (new_input[i])
// 	{
// 		if (!check_for_token(new_input, i, data))
// 		{
// 			data->argv[a] = split_with_q(new_input[i], ' ');
// 			a++;
// 			i++;
// 		}
// 		else
// 		{
// 			start = i;
// 			if (!check_for_cmd(data, new_input[i]))
// 			{
// 				while (new_input[i])
// 				{
// 					if (check_for_token(new_input, i, data))
// 						i++;
// 					else
// 						break ;
// 				}
// 			}
// 			else
// 				i++;
// 			new = (char **)malloc ((i - (start - 1)) * sizeof(char *));
// 			if (!new)
// 				printf("error new\n");
// 			new[i - start] = NULL;
// 			count = 0;
// 			while (start < i)
// 			{
// 				new[count] = ft_strdup(new_input[start]);
// 				count++;
// 				start++;
// 			}
// 			data->argv[a] = new;
// 			a++;
// 		}
// 	}
// 	freeup(new_input);
// }

// int	check_for_token(char **argv, int i, t_data *data)
// {
// 	if (!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
// 		|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
// 		|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
// 		|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
// 		|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
// 		return (0);
// 	else if (access(argv[i], F_OK | R_OK) != -1
// 		&& check_for_cmd(data, argv[i - 1]))
// 		return (0);
// 	return (1);
// }

// int	check_for_cmd(t_data *data, char *argv)
// {
// 	int		i;
// 	char	*cmd;
// 	char	*tmp;

// 	i = 0;
// 	while (data->cmdpath[i])
// 	{
// 		tmp = ft_strjoin(data->cmdpath[i], "/");
// 		cmd = ft_strjoin(tmp, argv);
// 		free(tmp);
// 		if (access(cmd, F_OK | X_OK) != -1)
// 		{
// 			free(cmd);
// 			return (0);
// 		}
// 		free(cmd);
// 		i++;
// 	}
// 	return (1);
// }

// int	count_argv(char **argv)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (argv[i])
// 	{
// 		if ((!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
// 			&& i > 0)
// 			count += 2;
// 		else if ((!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
// 			&& i == 0)
// 			count++;
// 		i++;
// 	}
// 	return (count + 1);
// }

// int	count_argv(char **argv, t_data *data)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (argv[i])
// 	{
// 		if ((!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
// 			&& i > 0)
// 			count == 2;
// 		else if ((!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
// 				|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
// 			&& i == 0)
// 			count++;
// 		else if (!check_for_cmd(data, argv[i]))
// 			count++;
// 		i++;
// 	}
// }
