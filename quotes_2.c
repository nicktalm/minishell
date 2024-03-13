/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:36:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/12 17:00:19 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(char *input, int i)
{
	char	*isspace;
	int		start;
	int		end;
	char	*value;
	char	*ret;

	end = 0;
	isspace = " \t\n\v\f\r\0";
	start = i;
	while (!ft_strchr(isspace, input[i]) && input[i] != '"' && input[i] != 39)
		i++;
	end = i;
	value = ft_substr(input, start, end - start);
	if (!ft_strncmp(value, "?", ft_strlen(value)))
		printf("error code\n");
	ret = getenv(value);
	return (check_env_2(ret, input, start, end));
}

char	*check_env_2(char *ret, char *input, int start, int end)
{
	char	*tmp;
	char	*tmp2;

	if (ret == NULL)
	{
		tmp = ft_substr(input, 0, start - 1);
		ret = ft_strjoin(tmp, input + end + 1);
		free(tmp);
		free(input);
	}
	else
	{
		tmp = ft_substr(input, 0, start - 1);
		tmp2 = ft_strjoin(tmp, ret);
		free(tmp);
		ret = ft_strjoin(tmp2, input + end);
		free(tmp2);
		free(input);
	}
	return (ret);
}
