/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:32:59 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/20 11:54:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *word, int letter)
{
	int	i;

	i = 0;
	while (word[i] != (char)letter)
	{
		if (word[i] == '\0')
			return (0);
		i++;
	}
	if (letter == '\0')
		return ((char *)(word + i));
	return ((char *)(word + i));
}
