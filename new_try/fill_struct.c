/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:20:47 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/11 16:43:12 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*fill_exe(char **q, char **eq, char *input, char **s)
{
	t_exe	*cmd;
	int		i;
	char	*e;

	i = 0;
	e = input + ft_strlen(input);
	cmd = (t_exe *)malloc (sizeof(cmd));
	if (!cmd)
		printf("error\n");
	cmd->type = EXECVE;
	cmd->argv = alloc_struct(s);
	cmd->argv[i] = ft_substr(input, ft_strlen(input) - ft_strlen(*q), *eq - *q);
	printf("argv[%i] = %s\n", i, cmd->argv[i]);
	while (check_next(*s, 'a'))
	{
		i++;
		get_token(s, e, q, eq);
		cmd->argv[i] = ft_substr(input, ft_strlen(input) - ft_strlen(*q), *eq - *q);
		printf("argv[%i] = %s\n", i, cmd->argv[i]);
	}
	return ((t_cmd *)cmd);
}

t_cmd	*fill_pipe(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = (t_pipe *)malloc (sizeof(cmd));
	if (!cmd)
		printf("error\n");
	cmd->type = PIPE;
	printf("type left = %i\n", left->type);
	printf("type right = %i\n", right->type);
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_redir(char **s, char **q, char **eq, t_cmd *c, char *input)
{
	t_redir	*cmd;
	char	*e;

	e = *s + ft_strlen(input);
	cmd = (t_redir *)malloc (sizeof(cmd));
	if (!cmd)
		printf("error\n");
	cmd->type = REDIR;
	if (**q == '>')
	{
		q++;
		if (**q == '>')
			cmd->mode = O_WRONLY | O_CREAT;
		else
			cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	else
	{
		cmd->mode = O_RDONLY;
		cmd->fd = 0;
	}
	get_token(s, e, q, eq);
	cmd->file = ft_substr(input, ft_strlen(input) - ft_strlen(*q), *eq - *q);
	if (c)
		cmd->cmd = c;
	else
		cmd->cmd = fill_exe(q, eq, input, s);
	return ((t_cmd *)cmd);
}

char	**alloc_struct(char **s)
{
	int		i;
	char	**argv;
	char	*new_s;
	char	*new_e;

	new_s = ft_strdup(*s);
	new_e = new_s + ft_strlen(new_s);
	i = 1;
	while (check_next(new_s, 'a'))
	{
		i++;
		get_token(&new_s, new_e, 0, 0);
	}
	argv = (char **)malloc ((i + 1) * sizeof(char *));
	if (!argv)
		printf("error\n");
	argv[i] = NULL;
	return (argv);
}
