/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:36:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/27 17:57:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(char *input, int i, t_data data)
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
	if (ft_strcmp(value, ""))
	{
		if (!ft_strcmp(value, "?"))
			ret = ft_itoa(Signal);
		else
			ret = get_env(value, &data.vars);
		return (check_env_2(ret, input, start, end));
	}
	else
		return (input);
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

char	*get_env(char *value, t_var **env)
{
	t_var	*lst;

	lst = *env;
	while (lst)
	{
		if (!ft_strcmp(lst->name, value))
			return (lst->value);
		lst = lst->nxt;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
