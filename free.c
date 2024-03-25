/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:52 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/25 15:18:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**freeup(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	free_ast(t_cmd *cmd)
{
	t_exe		*exe;
	t_pipe		*pipe;
	t_redir		*redir;
	t_here_doc	*here;

	if (cmd->type == EXECVE)
	{
		exe = (t_exe *)cmd;
		free_exe(exe);
	}
	else if (cmd->type == PIPE)
	{
		pipe = (t_pipe *)cmd;
		free_ast(pipe->left);
		free_ast(pipe->right);
		free(pipe);
	}
	else if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		free_ast(redir->cmd);
		free_redir(redir);
	}
	else if (cmd->type == HERE)
	{
		here = (t_here_doc *)cmd;
		free_ast(here->cmd);
		free_here(here);
	}
}

void	free_exe(t_exe	*node)
{
	freeup(node->argv);
	free(node);
}

void	free_redir(t_redir *node)
{
	free(node->f);
	free(node);
}

void	free_here(t_here_doc *node)
{
	free(node->l);
	free(node);
}

void	free_lst(t_var	**lst)
{
	t_var	*node;
	t_var	*tmp;

	if (lst)
	{
		node = *lst;
		while (node)
		{
			tmp = node->nxt;
			free(node->name);
			free(node->value);
			free(node);
			node = tmp;
		}
	}
}
