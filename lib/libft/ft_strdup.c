/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:08:52 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/20 10:51:46 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;

	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!(str))
		return (0);
	ft_strlcpy(str, s, ft_strlen(s) + 1);
	return (str);
}
