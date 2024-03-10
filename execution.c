/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:43:48 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/09 16:11:46 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_token **lst, t_data data)
{
	t_token	*node;
	char	*cmd;
	char	*tmp;
	char	**cmd_argv;

	cmd = NULL;
	if (*lst)
	{
		node = *lst;
		while (node)
		{
			if (!ft_strncmp(node->token, "op", ft_strlen(node->token)))
			{
				if (!ft_strncmp(node->input, "<", ft_strlen(node->input)))
				{
					printf("< op\n");
				}
				else if (!ft_strncmp(node->input, ">", ft_strlen(node->input)))
				{
					printf("> op\n");
				}
			}
			else if (!ft_strncmp(node->token, "word", ft_strlen(node->token)))
			{
				if (!cmd)
					cmd = ft_strjoin(node->input, " ");
				else
				{
					tmp = ft_strjoin(cmd, node->input);
					free(cmd);
					cmd = ft_strjoin(tmp, " ");
					free(tmp);
				}
			}
			node = node->next;
		}
	}
	cmd_argv = split_with_q(cmd, ' ');
	exe_other_test(data , cmd_argv);
}


void	exe_other_test(t_data data, char **cmd_argv)
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		error(ERROR_6);
	if (id == 0)
	{
		path = check_for_access(data, cmd_argv);
		if (!(path))
		{
			error(ERROR_8);
			exit(0);
		}
		else
		{
			if (execve(path, cmd_argv, data.cmdpath) == -1)
			{
				error(ERROR_4);
				exit(0);
			}
		}
	}
	if (id > 0)
	{
		waitpid(0, NULL, 0);
		// if (data.op)
		// {
		// 	if (!ft_strncmp(data.op, ">", ft_strlen(data.op)))
		// 	{
		// 		close(data.fd);
		// 		if (dup2(data.save_fd, STDOUT_FILENO) == -1)
		// 			printf("dup2 error\n");
		// 	}
		// 	else if (!ft_strncmp(data.op, "<", ft_strlen(data.op)))
		// 	{
		// 		close(data.fd);
		// 		if (dup2(data.save_fd, STDIN_FILENO) == -1)
		// 			printf("dup2 error\n");
		// 	}
		// }
	}
}