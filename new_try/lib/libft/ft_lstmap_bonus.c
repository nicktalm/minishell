/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:47:16 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/24 11:35:37 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	void	*current;

	newlst = NULL;
	if (!(f) || !(del))
		return (NULL);
	while (lst)
	{
		current = f(lst->content);
		newnode = ft_lstnew(current);
		if (!(newnode))
		{
			del(current);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&newlst, newnode);
			lst = lst->next;
		}
	}
	lst = NULL;
	return (newlst);
}
