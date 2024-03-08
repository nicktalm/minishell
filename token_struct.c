/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:21:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/08 17:24:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_lst(char *token, char *input, t_token **lst)
{
	t_token	*new;

	new = create_new_node(token, input);
	add_to_lst(lst, new);
}

t_token	*create_new_node(char *t, char *i)
{
	t_token	*new;

	new = (t_token *)malloc (sizeof(new));
	if (!new)
		printf("error\n");
	new->token = ft_strdup(t);
	new->input = ft_strdup(i);
	new->next = NULL;
	return (new);
}

void	add_to_lst(t_token **lst, t_token *new)
{
	t_token	*now;

	if (!(*lst))
		*lst = new;
	else
	{
		now = *lst;
		while (now->next)
			now = now->next;
		now->next = new;
	}
}
