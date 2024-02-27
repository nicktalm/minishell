/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:09:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/27 09:44:49 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input)
{
	char	**argv;
	t_data	data;
	t_tree	*tree;
	t_tree	*tree2;
	int		i;
	int		t;
	int		l;

	data.tree = NULL;
	data.leaf = NULL;
	argv = split_with_q(input, ' ');
	allocate_structs(argv, &data);
	i = count_strs(argv) - 1;
	t = 0;
	l = 0;
	recursive_parsing(argv, i, t, l, &data);
	tree = data.tree[0]->left;
	printf("tree 0\n");
	printf("opl = %s opr = %s\n", data.tree[0]->opl, data.tree[0]->opr);
	printf("left = %s right = %s\n", tree->opl, data.tree[0]->right);
	printf("tree 1\n");
	printf("opl = %s opr = %s\n", tree->opl, tree->opr);
	tree2 = tree->left;
	printf("left = %s right = %s\n", tree2->opl, tree->right);
}

void	recursive_parsing(char **argv, int i, int t, int l, t_data *data)
{
	if (i < 0)
	{
		printf("here\n");
		data->tree[t - 1]->left = data->leaf[l - 1]->input1;
		return ;
	}
	else if (!ft_strncmp(argv[i], "|", ft_strlen(argv[i])))
		add_to_struct(argv, data, i, t, l, "|");
	else if (!ft_strncmp(argv[i], "<", ft_strlen(argv[i])))
		add_to_struct(argv, data, i, t, l, "<");
	else if (!ft_strncmp(argv[i], ">", ft_strlen(argv[i])))
		add_to_struct(argv, data, i, t, l, ">");
	else if (!ft_strncmp(argv[i], "<<", ft_strlen(argv[i])))
		add_to_struct(argv, data, i, t, l, "<<");
	else if (!ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
		add_to_struct(argv, data, i, t, l, ">>");
	else
	{
		printf("a\n");
		data->leaf[l]->input1 = argv[i];
		if (i > 1)
			data->leaf[l]->input2 = argv[i - 2];
		recursive_parsing(argv, i - 1, t, l + 1, data);
	}
	return ;
}

void	add_to_struct(char **argv, t_data *data, int i, int t, int l, char *op)
{
	printf("%s\n", op);
	data->tree[t]->opl = op;
	if (t > 0)
		data->tree[t]->opr = data->tree[t - 1]->opl;
	else
		data->tree[t]->opr = NULL;
	if (t + 1 < count_trees(argv))
		data->tree[t]->left = data->tree[t + 1];
	data->tree[t]->right = data->leaf[l - 1]->input1;
	recursive_parsing(argv, i - 1, t + 1, l, data);
}

void	allocate_structs(char **argv, t_data *data)
{
	int	trees;
	int	leafs;
	int	i;

	trees = count_trees(argv);
	leafs = count_strs(argv) - trees;
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

int	count_trees(char **argv)
{
	int	i;
	int	trees;

	i = 0;
	trees = 0;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "|", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], "<", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], ">", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], "<<", ft_strlen(argv[i]))
			|| !ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
			trees++;
		i++;
	}
	return (trees);
}

int	count_strs(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

// void	exe_cmd(t_tree *tree)
// {
// 	if (tree->left)
// 	{
// 		if (!ft_strncmp(tree->opl, "<", ft_strlen(tree->opl))
// 			|| !ft_strncmp(tree->opl, ">", ft_strlen(tree->opl))
// 			|| !ft_strncmp(tree->opl, "<<", ft_strlen(tree->opl))
// 			|| !ft_strncmp(tree->opl, ">>", ft_strlen(tree->opl)))
// 			exe_redir(tree);
// 		else
// 			exe_pipe();
// 	}
// 	else
// 	{
		
// 	}
// }
