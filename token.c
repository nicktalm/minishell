/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:11:20 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/27 10:54:06 by lbohm            ###   ########.fr       */
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
	data->exe = NULL;
	while (*s)
	{
		token = get_token(&s, &q, &eq);
		if (token == '|')
		{
			if (check_next(s, 'a'))
			{
				get_token(&s, &q, &eq);
				data->exe = fill_exe(&q, &eq, input, &s);
				if (check_next(s, '<') || check_next(s, '>')
					|| check_next(s, '+'))
				{
					get_token(&s, &q, &eq);
					data->s_n = fill_pipe(data->s_n, fill_redir(&s, &q, &eq, data));
				}
				else if (check_next(s, '-'))
				{
					get_token(&s, &q, &eq);
					data->s_n = fill_pipe(data->s_n, fill_here_doc(&s, &q, &eq, data));
				}
				else
					data->s_n = fill_pipe(data->s_n, data->exe);
			}
			else if (check_next(s, '<') || check_next(s, '>')
				|| check_next(s, '+'))
			{
				get_token(&s, &q, &eq);
				if (check_next(s, 'a'))
					data->exe = fill_exe(0, 0, 0, 0);
				data->s_n = fill_pipe(data->s_n, fill_redir(&s, &q, &eq, data));
			}
			else if (check_next(s, '-'))
			{
				get_token(&s, &q, &eq);
				data->s_n = fill_pipe(data->s_n, fill_here_doc(&s, &q, &eq, data));
			}
		}
		else if (token == '>' || token == '<' || token == '+')
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

	isspace = " \t\n\v\f\r";
	while (ft_strchr(isspace, **s) && **s != '\0')
		(*s)++;
	*q = *s;
	if (**s == '\0')
		return (0);
	else if (!ft_strncmp(*s, "| ", 2) || !ft_strncmp(*s, "|", 2))
		ret = '|';
	else if (!ft_strncmp(*s, ">> ", 3) || !ft_strncmp(*s, ">>", 3))
		ret = '+';
	else if (!ft_strncmp(*s, "<< ", 3) || !ft_strncmp(*s, "<<", 3))
		ret = '-';
	else if (!ft_strncmp(*s, "< ", 2) || !ft_strncmp(*s, "<", 2))
		ret = '<';
	else if (!ft_strncmp(*s, "> ", 2) || !ft_strncmp(*s, ">", 2))
		ret = '>';
	else
	{
		ret = 'a';
		if (**s == '"' || **s == '\'')
		{
			find_end(s, q, eq, **s);
			return (ret);
		}
	}
	while (!ft_strchr(isspace, **s) && **s != '\0')
		(*s)++;
	*eq = *s;
	return (ret);
}

int	check_next(char *s, char t)
{
	char	*isspace;
	char	*tokens;

	isspace = " \t\n\v\f\r";
	tokens = "<|>";
	while (ft_strchr(isspace, *s) && *s)
		s++;
	if ((!ft_strncmp(s, "| ", 2) || !ft_strncmp(s, "|", 2)) && t == '|')
		return (1);
	else if ((!ft_strncmp(s, ">> ", 3) || !ft_strncmp(s, ">>", 3)) && t == '+')
		return (1);
	else if ((!ft_strncmp(s, "<< ", 3) || !ft_strncmp(s, "<<", 3)) && t == '-')
		return (1);
	else if ((!ft_strncmp(s, "< ", 2) || !ft_strncmp(s, "<", 2)) && t == '<')
		return (1);
	else if ((!ft_strncmp(s, "> ", 2) || !ft_strncmp(s, ">", 2)) && t == '>')
		return (1);
	else if (!ft_strchr(tokens, *s) && t == 'a')
		return (1);
	return (0);
}
