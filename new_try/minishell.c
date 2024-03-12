/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/12 17:28:43 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*input;

	data.cmd_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		input = print_prompt();
		input = check_for_quotes(input);
		if (ft_strncmp(input, "", ft_strlen(input)))
		{
			token(input, &data);
			test(data.start_node, &data);
			//exe_other(&data, data.start_node);
			free(input);
		}
	}
}

void	exe_other(t_data *data, t_cmd *cmd)
{
	t_exe	*exe;
	t_pipe	*pipe;

	exe = NULL;
	pipe = NULL;
	if (cmd->type == 0)
	{
		exe = (t_exe *)data->start_node;
		exe_execve(data, exe);
	}
	else if (cmd->type == 1)
	{
		pipe = (t_pipe *)data->start_node;
		exe_pipe(data, pipe);
	}
}

void	error(char *msg)
{
	perror(msg);
}

void	test(t_cmd *t, t_data *data)
{
	t_exe	*cmd;
	t_pipe	*cmd1;
	t_redir	*cmd2;
	int		i;

	i = 0;
	cmd = NULL;
	cmd1 = NULL;
	cmd2 = NULL;
	if (t->type == EXECVE)
	{
		cmd = (t_exe *)t;
		// while (cmd->argv[i])
		// {
		// 	printf("test argv[%i] = \033[1;33m %s \033[0m ", i, cmd->argv[i]);
		// 	i++;
		// }
		// printf("\n");
		exe_execve(data, cmd);
		return ;
	}
	else if (t->type == PIPE)
	{
		cmd1 = (t_pipe *)t;
		test(cmd1->left, data);
		test(cmd1->right, data);
	}
	else if (t->type == REDIR)
	{
		cmd2 = (t_redir *)t;
		printf("file = %s\n", cmd2->file);
		printf("mode = %i\n", cmd2->mode);
		printf("fd = %i\n", cmd2->fd);
		test(cmd2->cmd, data);
	}
}
