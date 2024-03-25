/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:16:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/25 18:02:07 by lbohm            ###   ########.fr       */
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
	tmp = free_used_string("\001\e[1;34m\002", user, 0, 0);
	user = free_used_string(tmp, "\001\e[0m\002", 1, 0);
	cwd = prompt_cwd();
	tmp = ft_substr(cwd, find_s(cwd), ft_strlen(cwd) - find_s(cwd));
	free(cwd);
	cwd = free_used_string(tmp, " ", 1, 0);
	tmp = free_used_string("\001\e[1;32m\002", cwd, 0, 1);
	cwd = free_used_string(tmp, "\001\e[0m\002", 1, 0);
	tmp = free_used_string(user, "$ ", 1, 0);
	prompt = free_used_string(cwd, tmp, 1, 1);
	input = readline(prompt);
	free(prompt);
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

char	*free_used_string(char *f, char *s, int ff, int sf)
{
	char	*tmp;

	tmp = ft_strjoin(f, s);
	if (ff == 1)
		free(f);
	if (sf == 1)
		free(s);
	return (tmp);
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
