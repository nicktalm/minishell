/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:20:47 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/13 17:40:26 by lbohm            ###   ########.fr       */
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
	t_pipe	*cmd;

	cmd = (t_pipe *)malloc (sizeof(t_pipe));
	if (!cmd)
		printf("error\n");
	cmd->type = PIPE;
	cmd->left = l;
	cmd->right = r;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_redir(char **s, char **q, char **eq, t_data *data)
{
	t_redir	*cmd;

	cmd = (t_redir *)malloc (sizeof(t_redir));
	if (!cmd)
		printf("error\n");
	cmd->type = REDIR;
	check_for_mode(&cmd, q);
	get_token(s, q, eq);
	cmd->f = ft_substr(data->in, ft_strlen(data->in) - ft_strlen(*q), *eq - *q);
	if (data->s_n && check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cmd->cmd = cat_struct(data->s_n, fill_exe(q, eq, data->in, s));
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

t_cmd	*fill_here_doc(char **s, char **q, char **eq, t_data *data)
{
	t_here_doc	*cmd;
	char		*tmp;

	cmd = (t_here_doc *)malloc (sizeof(t_here_doc));
	if (!cmd)
		printf("error\n");
	cmd->type = HERE;
	get_token(s, q, eq);
	tmp = ft_substr(data->in, ft_strlen(data->in) - ft_strlen(*q), *eq - *q);
	cmd->l = ft_strjoin(tmp, "\n");
	free(tmp);
	if (data->s_n && check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cmd->cmd = cat_struct(data->s_n, fill_exe(q, eq, data->in, s));
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
