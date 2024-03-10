/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:20:47 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/10 23:15:53 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*fill_exe(char **q, char **eq)
{
	t_exe	*cmd;

	cmd = (t_exe *)malloc (sizeof(cmd));
	if (!cmd)
		printf("error\n");
	cmd->type = "execve";
	cmd->argv[0] = *q;
	cmd->eargv[0] = *eq;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_pipe(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = (t_cmd *)malloc (sizeof(cmd));
	if (!cmd)
		printf("error\n");
	cmd->type = "pipe";
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_redir(char **s, char *e, char **q, char **eq, t_cmd *c, int mode, int fd)
{
	t_redir	*cmd;

	cmd = (t_cmd *)malloc (sizeof(cmd));
	if (!cmd)
		printf("error\n");
	cmd->type = "redir";
	get_token(s, e, q, eq);
	cmd->file = *q;
	cmd->efile = *eq;
	cmd->mode = mode;
	cmd->fd = fd;
	cmd->cmd = c;
	return ((t_cmd *)cmd);
}