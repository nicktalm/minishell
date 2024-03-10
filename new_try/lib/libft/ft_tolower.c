/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:18:30 by lbohm             #+#    #+#             */
/*   Updated: 2023/10/20 10:53:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int letter)
{
	if (!(ft_isalpha(letter)) || (letter > 96 && letter < 123))
		return (letter);
	else
		letter += 32;
	return (letter);
}
