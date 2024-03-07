/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CFG.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:50:26 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/07 16:34:06 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd_table(t_data *data)
{
	int		count;
	char	***cmd_table;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	count = count_trees(data->argv);
	cmd_table = (char ***)malloc ((count + 1) * sizeof(char **));
	if (!cmd_table)
		printf("error\n");
	cmd_table[count] = NULL;
	while (data->argv[i])
	{
		if (!ft_strncmp(data->argv[i][0], "<", ft_strlen(data->argv[i][0])))
		{
			printf("input redir\n");
			fill_cmd_table(data->argv, cmd_table, i, &pos, data);
			pos++;
		}
		else if (!ft_strncmp(data->argv[i][0], ">", ft_strlen(data->argv[i][0])))
		{
			printf("output redir\n");
			fill_cmd_table(data->argv, cmd_table, i, &pos, data);
			pos++;
		}
		else if (!ft_strncmp(data->argv[i][0], "<<", ft_strlen(data->argv[i][0])))
		{
			printf("here_doc\n");
			fill_cmd_table(data->argv, cmd_table, i, &pos, data);
			pos++;
		}
		else if (!ft_strncmp(data->argv[i][0], ">>", ft_strlen(data->argv[i][0])))
		{
			printf("output redir EOF\n");
			fill_cmd_table(data->argv, cmd_table, i, &pos, data);
			pos++;
		}
		else if (!ft_strncmp(data->argv[i][0], "|", ft_strlen(data->argv[i][0])))
		{
			printf("pipe\n");
			fill_cmd_table(data->argv, cmd_table, i, &pos, data);
			pos++;
		}
		i++;
	}
	int	a = 0;
	int	b = 0;
	while (cmd_table[a])
	{
		b = 0;
		while (b < 4)
		{
			printf("cmd_table[%i][%i] = %s\n", a, b, cmd_table[a][b]);
			b++;
		}
		a++;
	}
}

void	fill_cmd_table(char ***argv, char ***cmd_table, int i, int *pos, t_data *data)
{
	char	**cmd;

	cmd = (char **)malloc (5 * sizeof(char *));
	if (!cmd)
		printf("error\n");
	cmd_table[*pos] = cmd;
	cmd[4] = NULL;
	if (!ft_strncmp(argv[i][0], "<", ft_strlen(argv[i][0])))
	{
		if (i == 0)
		{
			cmd[0] = argv[i + 2][0];
			cmd[1] = argv[i + 2][1];
			cmd[2] = argv[i + 1][0];
			cmd[3] = argv[i][0];
		}
		else
		{
			cmd[0] = argv[i - 1][0];
			cmd[1] = argv[i - 1][1];
			cmd[2] = argv[i + 1][0];
			cmd[3] = argv[i][0];
		}
	}
	else if (!ft_strncmp(argv[i][0], ">", ft_strlen(argv[i][0]))
		|| !ft_strncmp(argv[i][0], ">>", ft_strlen(argv[i][0])))
	{
		if (i == 0)
		{
			cmd[0] = argv[i + 2][0];
			cmd[1] = argv[i + 2][1];
			cmd[2] = argv[i][0];
			cmd[3] = argv[i + 1][0];
		}
		else
		{
			cmd[0] = argv[i - 1][0];
			cmd[1] = argv[i - 1][1];
			cmd[2] = argv[i][0];
			cmd[3] = argv[i + 1][0];
		}
	}
	else if (!ft_strncmp(argv[i][0], "|", ft_strlen(argv[i][0])))
	{
		if (!check_for_cmd(data, argv[i - 1][0]))
		{
			cmd[0] = argv[i - 1][0];
			cmd[1] = argv[i - 1][1];
			cmd[2] = NULL;
			cmd[3] = argv[i][0];
		}
		else if (!check_for_cmd(data, argv[i - 3][0]))
		{
			cmd[0] = argv[i - 3][0];
			cmd[1] = argv[i - 3][1];
			cmd[2] = NULL;
			cmd[3] = argv[i][0];
		}
		else
			printf("error\n");
	}
	else if (!ft_strncmp(argv[i][0], "<<", ft_strlen(argv[i][0])))
	{
		if (i == 0)
		{
			printf("%i\n", count_argv(argv[i]));
			if ()
			{
				cmd[0] = NULL;
				cmd[1] = NULL;
				cmd[2] = argv[i][0];
				cmd[3] = argv[i + 1][0];
			}
			else
			{
				cmd[0] = argv[i + 2][0];
				cmd[1] = argv[i + 2][1];
				cmd[2] = argv[i + 1][0];
				cmd[3] = argv[i][0];
			}
		}
		else
		{
			cmd[0] = argv[i - 1][0];
			cmd[1] = argv[i - 1][1];
			cmd[2] = argv[i + 1][0];
			cmd[3] = argv[i][0];
		}
	}
}
