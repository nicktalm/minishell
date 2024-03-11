/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:11:20 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/11 17:11:53 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token(char *input, t_data *data)
{
	char	*s;
	char	*e;
	char	*q;
	char	*eq;
	char	token;
	int		i;

	i = 0;
	e = input + ft_strlen(input);
	s = input;
	q = NULL;
	eq = NULL;
	printf("%s\n", data->cmd_path[0]);
	while (*s != *e)
	{
		token = get_token(&s, e, &q, &eq);
		if (token == '|')
		{
			//printf("pipe\n");
			get_token(&s, e, &q, &eq);
			data->start_node = fill_pipe(data->start_node, fill_exe(&q, &eq, input, &s));
		}
		else if (token == '>')
		{
			//printf("output redir\n");
			//fill_redir();
		}
		else if (token == '<')
		{
			//printf("input redir\n");
		}
		else if (token == '+')
		{
			//printf("output redir EOF\n");
		}
		else if (token == '-')
		{
			//printf("here doc\n");
		}
		else if (token == 'a')
		{
			//printf("cmd\n");
			data->start_node = fill_exe(&q, &eq, input, &s);
			i++;
		}
	}
}

char	get_token(char **s, char *e, char **q, char **eq)
{
	char	*isspace;
	char	ret;

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
