/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:20:47 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/12 11:23:01 by lbohm            ###   ########.fr       */
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
	printf("r = %i\n", r->type);
	cmd->type = PIPE;
	cmd->left = l;
	cmd->right = r;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_redir(char **s, char **q, char **eq, t_cmd *c, char *input)
{
	t_redir	*cmd;

	cmd = (t_redir *)malloc (sizeof(t_redir));
	if (!cmd)
		printf("error\n");
	cmd->type = REDIR;
	check_for_mode(&cmd, q);
	get_token(s, q, eq);
	cmd->file = ft_substr(input, ft_strlen(input) - ft_strlen(*q), *eq - *q);
	if (c)
		cmd->cmd = c;
	else
	{
		get_token(s, q, eq);
		cmd->cmd = fill_exe(q, eq, input, s);
	}
	return ((t_cmd *)cmd);
}

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
			(*cmd)->mode = O_WRONLY | O_CREAT;
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
