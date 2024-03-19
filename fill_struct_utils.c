/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:31:00 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/19 10:08:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alloc_argv(char **s)
{
	int		i;
	char	**argv;
	char	*new_s;

	new_s = ft_strdup(*s);
	i = 1;
	while (check_next(new_s, 'a'))
	{
		i++;
		get_token(&new_s, 0, 0);
	}
	argv = (char **)malloc ((i + 1) * sizeof(char *));
	if (!argv)
		printf("error\n");
	argv[i] = NULL;
	return (argv);
}

void	check_for_mode(t_redir **cmd, char **q)
{
	if (**q == '>')
	{
		(*q)++;
		if (**q == '>')
			(*cmd)->mode = O_WRONLY | O_CREAT | O_APPEND;
		else
		{
			(*cmd)->mode = O_WRONLY | O_CREAT | O_TRUNC;
			(*q)--;
		}
		(*cmd)->fd = 1;
	}
	else
	{
		(*cmd)->mode = O_RDONLY;
		(*cmd)->fd = 0;
	}
}

void	cat_struct(t_cmd *new, t_cmd *cmd)
{
	t_exe	*first;
	t_exe	*second;
	int		pos;
	char	**argvs;

	first = (t_exe *)new;
	second = (t_exe *)cmd;
	pos = count_argvs(first->argv) + count_argvs(second->argv);
	argvs = (char **)malloc ((pos + 1) * sizeof(char *));
	if (!argvs)
		printf("error\n");
	argvs[pos] = NULL;
	argvs = cat_struct_2(first->argv, second->argv, argvs);
	freeup(first->argv);
	first->argv = argvs;
	freeup(second->argv);
	free(second);
}

char	**cat_struct_2(char **first, char **second, char **new)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (first[i])
	{
		new[pos] = ft_strdup(first[i]);
		i++;
		pos++;
	}
	i = 0;
	while (second[i])
	{
		new[pos] = ft_strdup(second[i]);
		i++;
		pos++;
	}
	return (new);
}

int	count_argvs(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
