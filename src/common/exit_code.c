/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:45:09 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 16:24:30 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"

void	set_exit_code(t_minishell *mnsh, int code)
{
	if (mnsh)
	{
		mnsh->parser_status = code;
		mnsh->last_exit_status = code;
	}
}
