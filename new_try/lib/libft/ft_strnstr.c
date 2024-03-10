/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:41:20 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/24 10:08:36 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *string, const char *word, size_t len)
{
	size_t	i;
	int		a;
	int		wordlen;

	if (len == 0 && string == NULL)
		return (NULL);
	wordlen = ft_strlen(word);
	if (wordlen == 0)
		return ((char *)(string));
	i = 0;
	while (string[i] != '\0')
	{
		a = 0;
		while (string[i + a] == word[a] && len > (i + a))
		{
			a++;
			if (word[a] == '\0')
				return ((char *)(string + i));
		}
		i++;
	}
	i = 0;
	return (NULL);
}
