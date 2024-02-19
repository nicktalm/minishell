/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:49:17 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/23 14:59:46 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*delete;
	t_list	*next;

	delete = *lst;
	while (delete)
	{
		next = delete->next;
		ft_lstdelone(delete, del);
		delete = next;
	}
	*lst = NULL;
}
