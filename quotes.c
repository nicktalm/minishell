/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/25 18:16:47 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_quotes(char *input, t_data data)
{
	int		i;
	int		double_q;
	int		single_q;
	int		first;

	i = 0;
	double_q = 0;
	single_q = 0;
	first = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == 39)
			double_or_single(&double_q, &single_q, input[i], &first);
		i++;
	}
	if (double_q == 1 || single_q == 1)
	{
		if (double_q == 1 && first == 100)
			return (wait_for_input('"', input, data));
		else if (single_q == 1 && first == 115)
			return (wait_for_input(39, input, data));
	}
	return (clean_input(input, data));
}

void	double_or_single(int *d, int *s, char quote, int *first)
{
	if (quote == '"')
	{
		if (*d == 1)
			*d = 0;
		else
		{
			if (*s == 0)
				*first = 100;
			*d = 1;
		}
	}
	else if (quote == 39)
	{
		if (*s == 1)
			*s = 0;
		else
		{
			if (*d == 0)
				*first = 115;
			*s = 1;
		}
	}
}

char	*wait_for_input(char quote, char *input, t_data data)
{
	char	*quote_prompt;
	char	*new_input;
	char	*tmp;
	char	*rest;

	quote_prompt = "\001\e[1;33m\002> \001\e[0m\002";
	new_input = ft_strjoin(input, "");
	free(input);
	rest = ft_strdup("");
	while (!ft_strchr(rest, quote))
	{
		free(rest);
		rest = readline(quote_prompt);
		tmp = free_used_string(new_input, rest, 1, 0);
		new_input = ft_strdup(tmp);
		free(tmp);
	}
	free(rest);
	return (clean_input(new_input, data));
}

char	*clean_input(char *input, t_data data)
{
	int	i;
	int	d_q;
	int	s_q;

	d_q = 0;
	s_q = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && s_q == 0)
			input = check_env(input, i + 1, data);
		else if (input[i] == '"' && s_q == 0)
			clean_input_2(input, i, &d_q);
		else if (input[i] == 39 && d_q == 0)
			clean_input_2(input, i, &s_q);
		i++;
	}
	return (input);
}

void	clean_input_2(char *input, int i, int *quote)
{
	if (*quote == 1)
		*quote = 0;
	else
		*quote = 1;
	input[i] = ' ';
}
