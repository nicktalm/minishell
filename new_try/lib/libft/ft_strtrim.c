/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:40:37 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/24 14:27:28 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[j - 1]) && j > i)
		j--;
	newstr = malloc((j - i + 1) * sizeof(char));
	if (!(newstr))
		return (NULL);
	ft_strlcpy(newstr, s1 + i, j - i + 1);
	return (newstr);
}
