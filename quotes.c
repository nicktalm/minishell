/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/08 12:20:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_quotes(char *input)
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
			return (wait_for_input('"', input));
		else if (single_q == 1 && first == 115)
			return (wait_for_input(39, input));
	}
	return (input);
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

char	*wait_for_input(char quote, char *input)
{
	char	*quote_promt;
	char	*new_input;
	char	*tmp;
	char	*rest;

	quote_promt = "\033[1;33m > \033[0m";
	new_input = ft_strjoin(input, "");
	free(input);
	rest = ft_strdup("");
	while (!ft_strchr(rest, quote))
	{
		free(rest);
		rest = readline(quote_promt);
		tmp = ft_strjoin(new_input, rest);
		free(new_input);
		new_input = ft_strdup(tmp);
		free(tmp);
	}
	free(rest);
	return (new_input);
}