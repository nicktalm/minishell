/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:11:20 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/13 17:33:39 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token(char *input, t_data *data)
{
	char	*s;
	char	*q;
	char	*eq;
	char	token;

	s = input;
	q = NULL;
	eq = NULL;
	data->s_n = NULL;
	while (*s)
	{
		token = get_token(&s, &q, &eq);
		if (token == '|')
		{
			if (check_next(s, 'a'))
			{
				get_token(&s, &q, &eq);
				data->s_n = fill_pipe(data->s_n, fill_exe(&q, &eq, input, &s));
			}
		}
		else if (token == '>')
			data->s_n = fill_redir(&s, &q, &eq, data);
		else if (token == '<')
			data->s_n = fill_redir(&s, &q, &eq, data);
		else if (token == '+')
			data->s_n = fill_redir(&s, &q, &eq, data);
		else if (token == '-')
			data->s_n = fill_here_doc(&s, &q, &eq, data);
		else if (token == 'a')
			data->s_n = fill_exe(&q, &eq, input, &s);
	}
}

char	get_token(char **s, char **q, char **eq)
{
	char	*isspace;
	char	ret;
	char	*e;

	e = *s + ft_strlen(*s);
	isspace = " \t\n\v\f\r";
	while (ft_strchr(isspace, **s) && **s != *e)
		(*s)++;
	if (q)
		*q = *s;
	if (**s == '|')
		ret = '|';
	else if (**s == '>')
	{
		ret = **s;
		(*s)++;
		if (**s == '>')
			ret = '+';
	}
	else if (**s == '<')
	{
		ret = **s;
		(*s)++;
		if (**s == '<')
			ret = '-';
	}
	else if (**s == *e)
		return (0);
	else
		ret = 'a';
	while (!ft_strchr(isspace, **s) && **s != *e)
		(*s)++;
	if (eq)
		*eq = *s;
	return (ret);
}

int	check_next(char *s, char token)
{
	char	*isspace;
	char	*tokens;

	isspace = " \t\n\v\f\r";
	tokens = "<|>";
	while (ft_strchr(isspace, *s) && *s)
		s++;
	if (*s == '|' && token == '|')
		return (1);
	else if (*s == '>' && token == '>')
		return (1);
	else if (*s == '<' && token == '<')
		return (1);
	else if (*s == '>' && token == '+')
	{
		s++;
		if (*s == '>')
			return (1);
	}
	else if (*s == '<' && token == '-')
	{
		s++;
		if (*s == '<')
			return (1);
	}
	else if (!ft_strchr(tokens, *s) && token == 'a')
		return (1);
	return (0);
}
