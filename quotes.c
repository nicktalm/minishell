/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/28 09:33:24 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_quotes(char *input, t_data data)
{
	int		i;
	int		double_q;
	int		single_q;
	int		first;
	char	*isspace;

	isspace = "\t\n\v\f\r";
	i = 0;
	double_q = 0;
	single_q = 0;
	first = 0;
	while (input[i])
	{
		if (ft_strchr(isspace, input[i]))
			input[i] = ' ';
		else if (input[i] == '"' || input[i] == '\'')
			double_or_single(&double_q, &single_q, input[i], &first);
		else if (input[i] == '$' && first != 115)
			input = check_env(input, i + 1, data);
		i++;
	}
	if ((double_q == 1 && first == 100) || (single_q == 1 && first == 115))
		perror("input error\n");
	return (clean_input(input));
}

char	*clean_input(char *input)
{
	char	*new;
	int		i;
	int		len;
	int		pos;
	int		q_len;

	i = 0;
	pos = 0;
	q_len = 0;
	len = clean_size(input);
	// printf("len =  %i\n", len);
	new = (char *)malloc ((len + 1) * sizeof(char));
	if (!new)
		error(ERROR_1);
	new[len] = '\0';
	while (input[i])
	{
		if (i == 0)
		{
			while (input[i] == ' ')
				i++;
		}
		if (input[i] == '"' && ft_strchr(input + (i + 1), '"'))
		{
			ft_strlcpy(new + pos, input + i, ft_strlen(input) - ft_strlen(ft_strchr(input + (i + 1), '"')) + 1);
			q_len = ft_strlen(input + i)
				- ft_strlen(ft_strchr(input + (i + 1), '"')) + 1;
			i += q_len;
			pos += q_len;
		}
		else if (input[i] == '"' && ft_strchr(input + (i + 1), '\''))
		{
			ft_strlcpy(new + pos, input + i, ft_strlen(input) - ft_strlen(ft_strchr(input + (i + 1), '\'')) + 1);
			q_len = ft_strlen(input + i)
				- ft_strlen(ft_strchr(input + (i + 1), '\'')) + 1;
			i += q_len;
			pos += q_len;
		}
		else if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			if (input[i])
			{
				new[pos] = input[i - 1];
				pos++;
			}
		}
		else
		{
			new[pos] = input[i];
			i++;
			pos++;
		}
	}
	free(input);
	return (new);
}

int	clean_size(char *input)
{
	int	i;
	int	len;
	int	q_len;

	i = 0;
	len = 0;
	q_len = 0;
	while (input[i])
	{
		if (i == 0)
		{
			while (input[i] == ' ')
				i++;
		}
		if (input[i] == '"' && ft_strchr(input + (i + 1), '"'))
		{
			q_len = ft_strlen(input + i)
				- ft_strlen(ft_strchr(input + (i + 1), '"')) + 1;
			i += q_len;
			len += q_len;
		}
		else if (input[i] == '\'' && ft_strchr(input + (i + 1), '\''))
		{
			q_len = ft_strlen(input + i)
				- ft_strlen(ft_strchr(input + (i + 1), '\'')) + 1;
			i += q_len;
			len += q_len;
		}
		else if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			if (input[i])
				len++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
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
	else if (quote == '\'')
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

void	find_end(char **s, char **q, char **eq, char quote)
{
	char	*isspace;

	isspace = " \t\n\v\f\r";
	(*s)++;
	*q = *s;
	while (**s != quote)
		(*s)++;
	*eq = *s;
	while (!ft_strchr(isspace, **s) && **s != '\0')
		(*s)++;
}

// char	*check_for_quotes(char *input, t_data data)
// {
// 	int		i;
// 	int		double_q;
// 	int		single_q;
// 	int		first;

// 	i = 0;
// 	double_q = 0;
// 	single_q = 0;
// 	first = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\t')
// 			input[i] = ' ';
// 		else if (input[i] == '"' || input[i] == '\'')
// 			double_or_single(&double_q, &single_q, input[i], &first);
// 		else if (input[i] == '$' && first != 115)
// 			input = check_env(input, i + 1, data);
// 		i++;
// 	}
// 	if ((double_q == 1 && first == 100) || (single_q == 1 && first == 115))
// 	{
// 		perror("input error\n");
// 		// if (double_q == 1 && first == 100)
// 		// 	return (wait_for_input('"', input, data));
// 		// else if (single_q == 1 && first == 115)
// 		// 	return (wait_for_input(39, input, data));
// 	}
// 	return (quote_input(input));
// }

// char	*quote_input(char *input)
// {
// 	char	*new;
// 	int		len;
// 	int		i;
// 	int		pos;

// 	i = 0;
// 	pos = 0;
// 	len = len_w_q(input);
// 	printf("input len = %zu\n", ft_strlen(input));
// 	printf("len = %i\n", len);
// 	new = (char *)malloc ((len + 1) * sizeof(char));
// 	if (!new)
// 		error(ERROR_1);
// 	new[len] = '\0';
// 	while (pos < len)
// 	{
// 		if (input[i] != '"')
// 		{
// 			printf("input[%i] = %c\n", i, input[i]);
// 			if (input[i] != '\'')
// 				new[pos] = '"';
// 			else
// 			{
// 				new[pos] = input[i];
// 				i++;
// 			}
// 			printf("new[%i] = %c\n", pos, new[pos]);
// 			pos++;
// 		}
// 		else
// 		{
// 			new[pos] = input[i];
// 			pos++;
// 			i++;
// 			while (input[i] != '"')
// 			{
// 				new[pos] = input[i];
// 				i++;
// 				pos++;
// 			}
// 			new[pos] = input[i];
// 			i++;
// 			pos++;
// 		}
// 		while (input[i] != ' ' && input[i])
// 		{
// 			printf("input[%i] = %c\n", i, input[i]);
// 			new[pos] = input[i];
// 			printf("new[%i] = %c\n", pos, new[pos]);
// 			i++;
// 			pos++;
// 		}
// 		if (input[i] == ' ' || input[i])
// 		{
// 			printf("input[%i] = %c\n", i, input[i]);
// 			if (new[pos - 1] != '"')
// 			{
// 				new[pos] = '"';
// 				printf("new[%i] = %c\n", pos, new[pos]);
// 				pos++;
// 			}
// 			new[pos] = input[i];
// 			printf("new[%i] = %c\n", pos, new[pos]);
// 			pos++;
// 			i++;
// 		}
// 	}
// 	free(input);
// 	return (new);
// }

// int	len_w_q(char *input)
// {
// 	int	len;
// 	int	i;
// 	int	quotes;

// 	len = 0;
// 	i = 0;
// 	quotes = 0;
// 	while (input[i])
// 	{
// 		printf("i = %i\n", i);
// 		if (input[i] == ' ')
// 		{
// 			len++;
// 			i++;
// 		}
// 		else if (input[i] == '"' || input[i] == '\'')
// 		{
// 			quotes++;
// 			if (input[i] == '"')
// 			{
// 				i++;
// 				while (input[i] != '"' && input[i])
// 					i++;
// 			}
// 			else
// 			{
// 				i++;
// 				while (input[i] != '\'' && input[i])
// 					i++;
// 			}
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
// 	len = (len + 1 - quotes) * 2;
// 	return (ft_strlen(input) + len);
// }

// char	*wait_for_input(char quote, char *input, t_data data)
// {
// 	char	*quote_prompt;
// 	char	*new_input;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*rest;

// 	quote_prompt = "\001\e[1;33m\002> \001\e[0m\002";
// 	new_input = ft_strdup(input);
// 	free(input);
// 	rest = ft_strdup("");
// 	while (!ft_strchr(rest, quote))
// 	{
// 		free(rest);
// 		rest = readline(quote_prompt);
// 		tmp = free_used_string(rest, "\n", 0, 0);
// 		tmp2 = free_used_string(new_input, tmp, 1, 1);
// 		new_input = ft_strdup(tmp2);
// 		free(tmp2);
// 	}
// 	free(rest);
// 	return (clean_input(new_input, data));
// }

// char	*clean_input(char *input, t_data data)
// {
// 	int		i;
// 	int		d_q;
// 	int		s_q;
// 	int		len;

// 	len = 0;
// 	d_q = 0;
// 	s_q = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '$' && s_q == 0)
// 			input = check_env(input, i + 1, data);
// 		else if (input[i] == '"' && s_q == 0)
// 			clean_input_2(&d_q);
// 		else if (input[i] == 39 && d_q == 0)
// 			clean_input_2(&s_q);
// 		else if ((input[i] == '\\' || input[i] == ';')
// 			&& d_q == 0 && s_q == 0)
// 			clean_input_2(0);
// 		i++;
// 	}
// 	return (trim_input(input));
// }

// char	*trim_input(char *input)
// {
// 	char	*new;
// 	int		i;
// 	int		d_q;
// 	int		s_q;
// 	int		pos;

// 	i = 0;
// 	d_q = 0;
// 	s_q = 0;
// 	pos = 0;
// 	new = (char *)malloc ((len_wout_q(input) + 1) * sizeof(char));
// 	if (!new)
// 		error(ERROR_1);
// 	new[len_wout_q(input)] = '\0';
// 	while (input[i])
// 	{
// 		if (input[i] == '"' && s_q == 0)
// 			clean_input_2(&d_q);
// 		else if (input[i] == 39 && d_q == 0)
// 			clean_input_2(&s_q);
// 		else if ((input[i] == '\\' || input[i] == ';')
// 			&& d_q == 0 && s_q == 0)
// 			clean_input_2(0);
// 		else
// 		{
// 			new[pos] = input[i];
// 			pos++;
// 		}
// 		i++;
// 	}
// 	free(input);
// 	return (new);
// }

// void	clean_input_2(int *quote)
// {
// 	if (quote)
// 	{
// 		if (*quote == 1)
// 			*quote = 0;
// 		else
// 			*quote = 1;
// 	}
// }

// int	len_wout_q(char *input)
// {
// 	int	len;
// 	int	i;
// 	int	d_q;
// 	int	s_q;

// 	d_q = 0;
// 	s_q = 0;
// 	len = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"' && s_q == 0)
// 			clean_input_2(&d_q);
// 		else if (input[i] == 39 && d_q == 0)
// 			clean_input_2(&s_q);
// 		else if ((input[i] == '\\' || input[i] == ';')
// 			&& d_q == 0 && s_q == 0)
// 			clean_input_2(0);
// 		else
// 			len++;
// 		i++;
// 	}
// 	return (len);
// }
