/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:06:28 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/20 10:51:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	unsigned char	*cpystr;
	size_t			i;

	cpystr = str;
	i = 0;
	while (len > i)
	{
		*cpystr = value;
		cpystr++;
		i++;
	}
	return ((void *)(str));
}
