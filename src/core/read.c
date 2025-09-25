/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:03:58 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/25 16:38:52 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

char	*ft_read_line(t_minishell *mnsh)
{
	char	*line;
	int		len;

	if (mnsh->is_tty_in)
		return (readline("minishell> "));
	line = get_next_line(STDIN);
	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	return (line);
}
