/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:34:36 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/24 10:22:39 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = dest;
	s = src;
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
