/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:35:26 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/13 17:29:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	int			byt_size;
	char		*finishline;

	byt_size = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer, &byt_size);
	if (byt_size == -1)
	{
		buffer = freeu(buffer);
		return (NULL);
	}
	if (!(buffer))
	{
		buffer = freeu(buffer);
		return (NULL);
	}
	finishline = clean_buffer(buffer);
	buffer = next_line(buffer);
	return (finishline);
}

char	*read_file(int fd, char *buffer, int *byt_size)
{
	char	*newline;

	newline = (char *)malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!(newline))
		return (freeu(buffer));
	while (*byt_size > 0)
	{
		*byt_size = read(fd, newline, BUFFER_SIZE);
		if (*byt_size <= 0)
		{
			free(newline);
			break ;
		}
		newline[*byt_size] = '\0';
		buffer = strjoin(buffer, newline);
		if (ft_strchrg(newline, '\n'))
		{
			free(newline);
			break ;
		}
	}
	return (buffer);
}

char	*strjoin(char *buffer, char *new)
{
	char	*str;
	int		i;
	int		j;

	if (!buffer)
	{
		buffer = (char *)malloc (1 * sizeof(char));
		if (!(buffer))
			return (NULL);
		buffer[0] = '\0';
	}
	if (!(buffer) || !(new))
		return (NULL);
	str = malloc((ft_strleng(buffer) + ft_strleng(new) + 1) * sizeof(char));
	if (!(str))
		return (freeu(buffer));
	i = -1;
	while (buffer[++i])
		str[i] = buffer[i];
	j = -1;
	while (new[++j])
		str[i + j] = new[j];
	str[i + j] = '\0';
	free(buffer);
	return (str);
}

char	*clean_buffer(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!(buffer))
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = (char *)malloc ((i + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	str[i] = '\0';
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i] = buffer[i];
	return (str);
}

char	*next_line(char *buffer)
{
	char	*nextline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(buffer))
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!(buffer[i]) || !(buffer[i + 1]))
		return (freeu(buffer));
	nextline = (char *)malloc ((ft_strleng(buffer) - i + 1) * sizeof(char));
	if (!(nextline))
		return (freeu(buffer));
	i++;
	j = 0;
	while (buffer[i])
		nextline[j++] = buffer[i++];
	nextline[j] = '\0';
	free(buffer);
	return (nextline);
}
