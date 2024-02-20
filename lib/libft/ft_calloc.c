/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:50:21 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/23 15:17:10 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*arr;

	total_size = count * size;
	arr = (char *)malloc(total_size * sizeof(char));
	if (!(arr))
		return (NULL);
	ft_memset(arr, '\0', total_size);
	return (arr);
}
