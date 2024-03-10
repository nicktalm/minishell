/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:16:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/06 10:20:30 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_prompt(void)
{
	char	*user;
	char	*cwd;
	char	*promt;
	char	*input;
	char	*tmp;

	user = getenv("USER");
	tmp = ft_strjoin("\033[1;34m", user);
	user = ft_strjoin(tmp, "\033[0m");
	free(tmp);
	cwd = promt_cwd();
	tmp = ft_substr(cwd, find_s(cwd), ft_strlen(cwd) - find_s(cwd));
	free(cwd);
	cwd = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin("\033[1;32m", cwd);
	free(cwd);
	cwd = ft_strjoin(tmp, "\033[0m");
	free(tmp);
	tmp = ft_strjoin(user, "$ ");
	free(user);
	promt = ft_strjoin(cwd, tmp);
	free(tmp);
	free(cwd);
	input = readline(promt);
	free(promt);
	return (input);
}

char	*promt_cwd(void)
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
	return (cwd);
}

int	find_s(char *pwd)
{
	int	len;

	len = ft_strlen(pwd);
	while (pwd[len - 1] != '/' && len > 0)
		len--;
	return (len);
}
