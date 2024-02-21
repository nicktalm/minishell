/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:09:41 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/20 18:13:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_with_q(char const *s, char c)
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

int	how_many_words(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word++;
			if (s[i] == 39)
			{
				i++;
				while (s[i] != 39)
					i++;
			}
			else
			{
				while (s[i] != c && s[i] != '\0')
					i++;
				if (s[i] == '\0')
					return (word);
			}
		}
		i++;
	}
	return (word);
}

char	*wordlen(char const *s, char c, int *p)
{
	char	*word;
	int		wordlen;

	wordlen = 0;
	while (s[*p] == c)
		(*p)++;
	while (s[*p] != c && s[*p] != '\0' && s[*p] != '\n')
	{
		if (s[*p] == 39 || s[*p] == '"')
			return (quotes((char *)s, p, s[*p]));
		else
		{
			(*p)++;
			wordlen++;
		}
	}
	word = (char *)malloc ((wordlen + 1) * sizeof(char));
	if (!(word))
		return (NULL);
	ft_strlcpy(word, s + (*p - wordlen), wordlen + 1);
	return (word);
}

char	**freeup(char	**arr)
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

char	*quotes(char *s, int *p, char quot)
{
	char	*word;
	int		wordlen;

	wordlen = 0;
	(*p)++;
	while (s[*p] != quot)
	{
		(*p)++;
		wordlen++;
	}
	(*p)++;
	word = (char *)malloc ((wordlen + 1) * sizeof(char));
	if (!(word))
		return (NULL);
	ft_strlcpy(word, s + (*p - wordlen - 1), wordlen + 1);
	return (word);
}
