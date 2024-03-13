/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:16:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/13 12:58:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_prompt(void)
{
	char	*user;
	char	*cwd;
	char	*prompt;
	char	*input;
	char	*tmp;

	user = getenv("USER");
	tmp = ft_strjoin("\001\e[1;34m\002", user);
	user = ft_strjoin(tmp, "\001\e[0m\002");
	free(tmp);
	cwd = prompt_cwd();
	tmp = ft_substr(cwd, find_s(cwd), ft_strlen(cwd) - find_s(cwd));
	free(cwd);
	cwd = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin("\001\e[1;32m\002", cwd);
	free(cwd);
	cwd = ft_strjoin(tmp, "\001\e[0m\002");
	free(tmp);
	tmp = ft_strjoin(user, "$ ");
	free(user);
	prompt = ft_strjoin(cwd, tmp);
	free(tmp);
	free(cwd);
	input = readline(prompt);
	free(prompt);
	add_history(input);
	return (input);
}

char	*prompt_cwd(void)
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
