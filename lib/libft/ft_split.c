/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:59:42 by lbohm             #+#    #+#             */
/*   Updated: 2023/12/21 11:56:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	how_many_words(char const *s, char c);
static char	*wordlen(char const *s, char c, int *p);
static char	**freeup(char	**arr);

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**arr;
	int		i;
	int		position;

	word = how_many_words(s, c);
	arr = (char **)malloc ((word + 1) * sizeof(char *));
	if (!(arr))
		return (NULL);
	position = 0;
	i = 0;
	while (i < word)
	{
		arr[i] = wordlen(s, c, &position);
		if (!(arr[i]))
		{
			freeup(arr);
			return (NULL);
		}
		i++;
	}
	arr[word] = NULL;
	return (arr);
}

static int	how_many_words(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				return (word);
		}
		i++;
	}
	return (word);
}

static char	*wordlen(char const *s, char c, int *p)
{
	char	*word;
	int		wordlen;

	wordlen = 0;
	while (s[*p] == c)
		(*p)++;
	while (s[*p] != c && s[*p] != '\0')
	{
		(*p)++;
		wordlen++;
	}
	word = (char *)malloc ((wordlen + 1) * sizeof(char));
	if (!(word))
		return (NULL);
	ft_strlcpy(word, s + (*p - wordlen), wordlen + 1);
	return (word);
}

static char	**freeup(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
