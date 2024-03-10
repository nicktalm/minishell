/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/03/10 22:46:53 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*input;

	data.cmd_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		input = print_prompt();
		input = check_for_quotes(input);
		token(input);
		free(input);
	}
}

void	error(char *msg)
{
	perror(msg);
}