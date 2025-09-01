/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:08:38 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/20 12:19:14 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_defs.h"
# include <stdarg.h>
# include <stddef.h>

/**
 * @brief  This function parses the format string and fills the
 *  t_format structure.
 * @param  format: Format of output string.
 * @param  cur: Pointer to the t_format structure to fill.
 * @retval None
 */
size_t	ft_parse(const char *format, t_format *cur);

#endif