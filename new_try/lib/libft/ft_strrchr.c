/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:02:36 by lbohm             #+#    #+#             */
/*   Updated: 2023/12/15 18:43:39 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *word, int letter)
{
	int	size;

	size = ft_strlen(word);
	while (size >= 0)
	{
		if (word[size] == (char)letter)
			return ((char *)(word + size));
		size--;
	}
	return (0);
}
