/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:43:55 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/24 10:36:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	a;

	a = 0;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < size)
		i++;
	while (src[a] != '\0' && i + a + 1 < size)
	{
		dst[i + a] = src[a];
		a++;
	}
	if (i + a < size)
		dst[i + a] = '\0';
	while (src[a] != '\0')
		a++;
	return (i + a);
}
