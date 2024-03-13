/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/13 12:05:51 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cd(char *path)
{
	if (chdir(path))
		error(ERROR_12);
}

void	exe_pwd(void)
{
	char	*cwd;
	int		size;

	size = 1;
	cwd = malloc(size * sizeof(char));
	if (!cwd)
		error(ERROR_1);
	while (getcwd(cwd, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size++;
			free(cwd);
			cwd = malloc(size * sizeof(char));
			if (!cwd)
				error(ERROR_1);
		}
		else
			error(ERROR_11);
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	exe_exit(void)
{
	// alles free, was allokiert wird
	printf("here\n");
	exit(0);
}

void	ctrl_c(int signal)
{
	signal = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
