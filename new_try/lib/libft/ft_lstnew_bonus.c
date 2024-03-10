/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:03 by lbohm             #+#    #+#             */
/*   Updated: 2023/12/14 20:43:28 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ((t_list *)malloc (sizeof(*new)));
	if (!(new))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
