/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:11:20 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/10 23:04:28 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token(char *input)
{
	char	*s;
	char	*e;
	char	*q;
	char	*eq;
	char	token;

	e = input + ft_strlen(input);
	s = input;
	q = NULL;
	eq = NULL;
	while (*s != *e)
	{
		token = get_token(&s, e, &q, &eq);
		if (token == '|')
		{
			printf("pipe\n");
			//data->start_node = fill_pipe();
		}
		if (token == '>')
		{
			printf("output redir\n");
		}
		if (token == '<')
		{
			printf("input redir\n");
		}
		if (token == '+')
		{
			printf("output redir EOF\n");
		}
		if (token == '-')
		{
			printf("here doc\n");
		}
		if (token == 'a')
		{
			printf("cmd\n");
			//data->start_node = fill_exe(e, &q, &eq);
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
	else
		ret = 'a';
	while (!ft_strchr(isspace, **s) && **s != *e)
		(*s)++;
	*eq = *s;
	return (ret);
}

