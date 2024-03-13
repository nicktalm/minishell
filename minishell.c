/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/13 12:09:53 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*input;
	pid_t	id;

	data.cmd_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		input = print_prompt();
		input = check_for_quotes(input);
		if (ft_strncmp(input, "", ft_strlen(input)))
		{
			token(input, &data);
			id = fork();
			if (id < 0)
				error(ERROR_6);
			else if (id == 0)
				test(data.start_node, &data);
			else if (id > 0)
				waitpid(0, NULL, 0);
			free(input);
		}
	}
}

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

void	test(t_cmd *t, t_data *data)
{
	t_exe	*cmd;
	t_pipe	*cmd1;
	t_redir	*cmd2;

	cmd = NULL;
	cmd1 = NULL;
	cmd2 = NULL;
	if (t->type == EXECVE)
	{
		cmd = (t_exe *)t;
		exe_execve(data, cmd);
		return ;
	}
	else if (t->type == PIPE)
	{
		cmd1 = (t_pipe *)t;
		exe_pipe(data, cmd1);
	}
	else if (t->type == REDIR)
	{
		cmd2 = (t_redir *)t;
		exe_redir(data, cmd2);
	}
}
