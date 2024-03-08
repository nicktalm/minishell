/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_CFG.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:05:23 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/08 19:32:55 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tokens(char *input, t_token **lst)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	*lst = NULL;
	while (input[i])
	{
		if (ft_isdigit(input[i]) && (ft_isdigit(input[i + 1]) || input[i + 1] == ' ' || !input[i + 1]))
		{
			start = i;
			i++;
			if (ft_isdigit(input[i]))
			{
				while (ft_isdigit(input[i]))
					i++;
				end = i;
				fill_lst("number", ft_substr(input, start, end - start), lst);
			}
			else
				fill_lst("digit", ft_substr(input, start, 1), lst);
		}
		else if (ft_isop(input[i]))
		{
			start = i;
			if (!check_after_cmd("+", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd("-", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd("*", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd("/", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd("|", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd("<", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd("<<", input, i))
			{
				fill_lst("op", ft_substr(input, start, 2), lst);
				i++;
			}
			else if (!check_after_cmd(">", input, i))
				fill_lst("op", ft_substr(input, start, 1), lst);
			else if (!check_after_cmd(">>", input, i))
			{
				fill_lst("op", ft_substr(input, start, 2), lst);
				i++;
			}
			if (input[i] == '-' && ft_isalpha(input[i + 1]))
			{
				start = i;
				i++;
				if (ft_isalpha(input[i]))
				{
					while (ft_isalpha(input[i]))
						i++;
					end = i;
					fill_lst("argv for cmd", ft_substr(input, start, end - start), lst);
				}
			}
		}
		else if (input[i] == '"')
		{
			start = i;
			i++;
			while (input[i] != '"')
				i++;
			end = i + 1;
			fill_lst("double quotes", ft_substr(input, start, end - start), lst);
		}
		else if (input[i] == 39)
		{
			start = i;
			i++;
			while (input[i] != 39)
				i++;
			end = i + 1;
			fill_lst("single quotes", ft_substr(input, start, end - start), lst);
		}
		else if (input[i] != ' ')
		{
			start = i;
			while (input[i] != ' ' && input[i])
				i++;
			end = i;
			fill_lst("word", ft_substr(input, start, end - start), lst);
		}
		i++;
	}
	free(input);
}

int	ft_isop(int op)
{
	if (op == '-' || op == '>' || op == '<'
		|| op == '+' || op == '-' || op == '*'
		|| op == '/' || op == '|')
		return (1);
	return (0);
}

int	check_after_cmd(char *str, char *input, int i)
{
	int	pos;

	pos = 0;
	if (i == 0 || input[i - 1] == ' ')
	{
		while (str[pos])
		{
			if (input[i] != str[pos])
				return (1);
			pos++;
			i++;
		}
		if (!input[i] || input[i] == ' ')
			return (0);
		else
			return (1);
	}
	return (1);
}
