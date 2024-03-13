/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:30:10 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/13 17:29:06 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*writeline(char *buffer, int fd, int *byt_size)
{
	buffer = read_file(fd, buffer, byt_size);
	if (*byt_size == -1)
		buffer = freeu(buffer);
	if (!(buffer))
		return (NULL);
	return (buffer);
}

char	*ft_strchrg(const char *word, int letter)
{
	int	i;

	i = 0;
	if (!(word))
		return (NULL);
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

size_t	ft_strleng(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*freeu(char *buffer)
{
	if (buffer)
		free(buffer);
	return (NULL);
}
