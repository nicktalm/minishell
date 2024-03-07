/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:09:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/06 18:10:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_tree(t_data data)
{
	int		i;
	int		t;
	int		l;

	data.tree = NULL;
	data.leaf = NULL;
	allocate_structs(&data);
	i = count_strs(data.argv) - 1;
	t = 0;
	l = 0;
	recursive_parsing(i, t, l, &data);
}

void	recursive_parsing(int i, int t, int l, t_data *d)
{
	if (i < 0)
	{
		if (t > 0)
			d->tree[t - 1]->left = d->leaf[l - 1];
		return ;
	}
	else if (!ft_strncmp(d->argv[i][0], "|", ft_strlen(d->argv[i][0])))
		add_to_struct(i, t, l, d);
	else if (!ft_strncmp(d->argv[i][0], "<", ft_strlen(d->argv[i][0])))
		add_to_struct(i, t, l, d);
	else if (!ft_strncmp(d->argv[i][0], ">", ft_strlen(d->argv[i][0])))
		add_to_struct(i, t, l, d);
	else if (!ft_strncmp(d->argv[i][0], "<<", ft_strlen(d->argv[i][0])))
		add_to_struct(i, t, l, d);
	else if (!ft_strncmp(d->argv[i][0], ">>", ft_strlen(d->argv[i][0])))
		add_to_struct(i, t, l, d);
	else
	{
		d->leaf[l]->input1 = d->argv[i];
		if (i < count_strs(d->argv) - 1)
		{
			if (!ft_strncmp(d->argv[i + 1][0], "|", ft_strlen(d->argv[i + 1][0])))
				d->leaf[l]->input2 = d->argv[i + 1];
			else
				d->leaf[l]->input2 = d->argv[i + 2];
		}
		else
			d->leaf[l]->input2 = NULL;
		recursive_parsing(i - 1, t, l + 1, d);
	}
	// if (t < count_trees(d->argv))
	// 	exe_tree(d->tree[t], t, d);
	// else
	// 	return ;
	if (count_strs(d->argv) - 1 == 0)
		return (exe_cmd(d->leaf[l], 0, d));
	else if (t == 0 && l == 0)
		return ;
	else if (t == 0)
		return (exe_cmd(d->leaf[l], 0, d));
	else
	{
		return (exe_cmd(d->tree[t - 1], 1, d));
	}
}

void	add_to_struct(int i, int t, int l, t_data *data)
{
	data->tree[t]->op = data->argv[i][0];
	if (t + 1 < count_trees(data->argv))
		data->tree[t]->left = data->tree[t + 1];
	data->tree[t]->right = data->leaf[l - 1];
	recursive_parsing(i - 1, t + 1, l, data);
}

void	allocate_structs(t_data *data)
{
	int	trees;
	int	leafs;
	int	i;

	trees = count_trees(data->argv);
	leafs = count_strs(data->argv) - trees;
	data->tree = (t_tree **)malloc (trees * sizeof(t_tree *));
	if (!data->tree)
		printf("error trees\n");
	data->leaf = (t_leaf **)malloc (leafs * sizeof(t_leaf *));
	if (!data->leaf)
		printf("error leafs\n");
	i = 0;
	while (trees > i)
	{
		data->tree[i] = (t_tree *)malloc (sizeof(*(data)->tree[i]));
		if (!data->tree[i])
			printf("error tree pointer\n");
		i++;
	}
	i = 0;
	while (leafs > i)
	{
		data->leaf[i] = (t_leaf *)malloc (sizeof(*(data)->leaf[i]));
		if (!data->leaf[i])
			printf("error leaf pointer\n");
		i++;
	}
}

int	count_trees(char ***argv)
{
	int	i;
	int	trees;

	i = 0;
	trees = 0;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i][0], "|", ft_strlen(argv[i][0]))
			|| !ft_strncmp(argv[i][0], "<", ft_strlen(argv[i][0]))
			|| !ft_strncmp(argv[i][0], ">", ft_strlen(argv[i][0]))
			|| !ft_strncmp(argv[i][0], "<<", ft_strlen(argv[i][0]))
			|| !ft_strncmp(argv[i][0], ">>", ft_strlen(argv[i][0])))
			trees++;
		i++;
	}
	return (trees);
}

int	count_strs(char ***argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	exe_cmd(void *tree, int i, t_data *data)
{
	t_tree	*t;
	t_leaf	*l;

	if (i == 1)
	{
		t = tree;
		data->op = t->op;
		if (t->left)
		{
			if (!ft_strncmp(t->op, "<", ft_strlen(t->op))
				|| !ft_strncmp(t->op, ">", ft_strlen(t->op))
				|| !ft_strncmp(t->op, "<<", ft_strlen(t->op))
				|| !ft_strncmp(t->op, ">>", ft_strlen(t->op)))
				exe_redir(t, data);
			// else
			// 	exe_pipe();
		}
		// else
		// {
				
		// }
	}
	else
	{
		l = tree;
		if (count_strs(data->argv) < 2)
			data->op = NULL;
		if (!ft_strncmp(l->input1[0], "cd", ft_strlen(l->input1[0])))
			exe_cd(l->input1[1]);
		else if (!ft_strncmp(l->input1[0], "pwd", ft_strlen(l->input1[0])))
			exe_pwd();
		else if (!ft_strncmp(l->input1[0], "exit", ft_strlen(l->input1[0])))
			exe_exit();
		else
			exe_other(data, l);
	}
}

void	exe_redir(t_tree *tree, t_data *data)
{
	t_leaf	*leaf;

	leaf = tree->left;
	if (!ft_strncmp(tree->op, ">", ft_strlen(tree->op)))
	{
		data->fd = open(leaf->input2[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->save_fd = dup(STDOUT_FILENO);
		if (data->save_fd == -1)
			printf("error fd\n");
		if (dup2(data->fd, STDOUT_FILENO) == -1)
			printf("error\n");
	}
	else if (!ft_strncmp(tree->op, "<", ft_strlen(tree->op)))
	{
		data->fd = open(leaf->input2[0], O_RDONLY);
		data->save_fd = dup(STDIN_FILENO);
		if (data->save_fd == -1)
			printf("error fd\n");
		if (dup2(data->fd, STDIN_FILENO) == -1)
			printf("error\n");
	}
}
