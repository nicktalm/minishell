//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:20:47 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/19 10:12:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*fill_exe(char **q, char **eq, char *in, char **s)
{
	t_exe	*cmd;
	int		i;

	i = 0;
	cmd = (t_exe *)malloc (sizeof(t_exe));
	if (!cmd)
		printf("error\n");
	cmd->type = EXECVE;
	cmd->argv = alloc_argv(s);
	cmd->argv[i] = ft_substr(in, ft_strlen(in) - ft_strlen(*q), *eq - *q);
	while (check_next(*s, 'a'))
	{
		i++;
		get_token(s, q, eq);
		cmd->argv[i] = ft_substr(in, ft_strlen(in) - ft_strlen(*q), *eq - *q);
	}
	return ((t_cmd *)cmd);
}

t_cmd	*fill_pipe(t_cmd *l, t_cmd *r)
{
	t_pipe		*cmd;
	t_here_doc	*doc;
	t_redir		*redir;

	cmd = (t_pipe *)malloc (sizeof(t_pipe));
	if (!cmd)
		printf("error\n");
	cmd->type = PIPE;
	if (l->type == HERE)
	{
		doc = (t_here_doc *)l;
		cmd->left = doc->cmd;
		cmd->right = r;
		doc->cmd = (t_cmd *)cmd;
		return ((t_cmd *)doc);
	}
	else if (l->type == REDIR)
	{
		redir = (t_redir *)l;
		cmd->left = redir->cmd;
		cmd->right = r;
		redir->cmd = (t_cmd *)cmd;
		return ((t_cmd *)redir);
	}
	else
		cmd->left = l;
	cmd->right = r;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_redir(char **s, char **q, char **eq, t_data *data)
{
	t_redir		*cmd;
	t_here_doc	*doc;
	t_redir		*check;

	cmd = (t_redir *)malloc (sizeof(t_redir));
	if (!cmd)
		printf("error\n");
	cmd->type = REDIR;
	check_for_mode(&cmd, q);
	get_token(s, q, eq);
	cmd->f = ft_substr(data->in, ft_strlen(data->in) - ft_strlen(*q), *eq - *q);
	if (data->s_n)
	{
		if (check_next(*s, 'a'))
		{
			get_token(s, q, eq);
			cat_struct(search_next(data->s_n, EXECVE), fill_exe(q, eq, data->in, s));
		}
		else if (data->s_n->type == HERE)
		{
			doc = (t_here_doc *)data->s_n;
			cmd->cmd = doc->cmd;
			doc->cmd = (t_cmd *)cmd;
			return ((t_cmd *)doc);
		}
		else if (data->s_n->type == REDIR)
		{
			check = (t_redir *)data->s_n;
			if (check->fd == 1)
			{
				cmd->cmd = check->cmd;
				check->cmd = (t_cmd *)cmd;
				return ((t_cmd *)check);
			}
		}
		cmd->cmd = data->s_n;
	}
	else if (check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cmd->cmd = fill_exe(q, eq, data->in, s);
	}
	else
		cmd->cmd = NULL;
	return ((t_cmd *)cmd); 
}

t_cmd	*search_next(t_cmd *cmd, int type)
{
	t_pipe		*cmd1;
	t_redir		*cmd2;
	t_here_doc	*cmd3;

	cmd1 = NULL;
	cmd2 = NULL;
	cmd3 = NULL;
	while (cmd->type != type)
	{
		if (cmd->type == PIPE)
		{
			cmd1 = (t_pipe *)cmd;
			return (cmd1->right);
		}
		else if (cmd->type == REDIR)
		{
			cmd2 = (t_redir *)cmd;
			cmd = cmd2->cmd;
			continue ;
		}
		else if (cmd->type == HERE)
		{
			cmd3 = (t_here_doc *)cmd;
			cmd = cmd3->cmd;
			continue ;
		}
	}
	return (cmd);
}

t_cmd	*fill_here_doc(char **s, char **q, char **eq, t_data *data)
{
	t_here_doc	*cmd;

	cmd = (t_here_doc *)malloc (sizeof(t_here_doc));
	if (!cmd)
		printf("error\n");
	cmd->type = HERE;
	get_token(s, q, eq);
	cmd->l = ft_substr(data->in, ft_strlen(data->in) - ft_strlen(*q), *eq - *q);
	if (data->s_n && check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cat_struct(search_next(data->s_n, EXECVE), fill_exe(q, eq, data->in, s));
		cmd->cmd = data->s_n;
	}
	else if (data->s_n)
		cmd->cmd = data->s_n;
	else if (check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cmd->cmd = fill_exe(q, eq, data->in, s);
	}
	else
		cmd->cmd = NULL;
	return ((t_cmd *)cmd);
}
