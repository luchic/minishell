/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:43:36 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:59:22 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "ft_defs.h"
# include <stdarg.h>
# include <stddef.h>

// ======== ft_format_utils.c ========
int				ft_fillspace(int size, char char_to_fill, int fd);
void			ft_asterisk_handler(t_format *cur, va_list ap);

// ======== ft_number_utils.c ========
int				ft_getsize_unsigned(unsigned long num, int base);
int				ft_getsize_signed(long num, int base);
unsigned int	ft_unsigned(int num);
int				ft_getsize_numformat(unsigned int unum, t_format *cur);

// ======== ft_flag_parser.c ========
int				ft_get_datatype(char c);
int				ft_get_flag(const char *format);
int				ft_isflag(char c);
int				ft_istype(char c);
int				ft_is_valid_char(char c);

// ======== ft_format_validator.c  ========
size_t			ft_set_none(t_format *cur);
void			ft_reset(t_format *cur);
void			ft_validate_format(t_format *cur);
void			ft_set_type(char c, t_format *cur);

// ======== ft_platform_utils.c ========
void			ft_null_check(void *ptr, t_format *cur);

// ======== ft_ptr_format.c ========
int				ft_size_ptr(void *ptr, t_format *cur);
int				ft_print_nullptr(void *ptr, int fd);
int				ft_puthex_fd(unsigned long num, int fd);

#endif