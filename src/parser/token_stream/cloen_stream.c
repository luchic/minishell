/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloen_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:41:55 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:29:54 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tokenstream	*ts_clone(t_tokenstream *src)
{
	t_tokenstream	*clone;

	clone = ft_calloc(1, sizeof(t_tokenstream));
	if (!clone)
		return (NULL);
	clone->cur = src->cur;
	return (clone);
}