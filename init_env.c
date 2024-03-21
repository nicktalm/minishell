/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:29:58 by ntalmon           #+#    #+#             */
/*   Updated: 2024/03/21 13:02:52 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_lstnew_new(char *name, char *value)
{
	t_var	*new;

	new = ((t_var *)malloc (sizeof(*new)));
	if (!(new))
		return (NULL);
	new->name = name;
	new->value = value;
	new->nxt = NULL;
	return (new);
}

void	ft_lstadd_back_new(t_var **lst, t_var *new)
{
	t_var	*now;

	if (!(*lst))
		*lst = new;
	else
	{
		now = *lst;
		while (now->nxt)
			now = now->nxt;
		now->nxt = new;
	}
}

void	init_env(char **env, t_var **vars)
{
	int		index;
	char	*equal_sign;
	int		name_len;

	index = 0;
	while (env[index] != NULL)
	{
		equal_sign = ft_strchr(env[index], '=');
		if (equal_sign != NULL)
		{
			name_len = equal_sign - env[index];
			ft_lstadd_back_new(vars, ft_lstnew_new(ft_substr(env[index],
						0, name_len), ft_substr(equal_sign + 1,
						0, ft_strlen(equal_sign + 1))));
			// printf("%s", vars[num_vars].name);
			// printf("%s", vars[num_vars].value);
		}
		// printf("\n");
		index++;
	}
}
