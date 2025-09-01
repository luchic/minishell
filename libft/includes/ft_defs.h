/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:24:39 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:39:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFS_H
# define FT_DEFS_H

# include <stdarg.h>
# include <stddef.h>

# if defined(__linux__)
#  define PTRNULL "(nil)"
#  define NPTRSIZE 5
# elif defined(__APPLE__)
#  define PTRNULL "0x0"
#  define NPTRSIZE 3
# endif

/**
 * @brief  Data type enum, that contains all possible
 *     data types for formating output string.
 */
typedef enum e_data
{
	NONE,
	CHAR,
	INT,
	UINT,
	LONG,
	ULONG,
	STR,
	PTR,
}					t_datatype;

/**
 * @brief The enum, that contains all possible flags
 *     for formating output string.
 NO_FLAG 		= 0,
 FLAG_MINUS 	= 1 << 0, // '-'
 FLAG_ZERO		= 1 << 1, // '0'
 FLAG_DOT		= 1 << 2, // '.'
 FLAG_HASH 		= 1 << 3, // '#'
 FLAG_PLUS 		= 1 << 4, // '+'
 FLAG_SPACE 	= 1 << 5, // ' '
 FLAG_PAST 		= 1 << 6, // '.*' For presision
 FLAG_DAST 		= 1 << 7, // '*' For width
 * @retval None
 */
typedef enum e_flags
{
	NO_FLAG = 0,
	FLAG_MINUS = 1 << 0,
	FLAG_ZERO = 1 << 1,
	FLAG_DOT = 1 << 2,
	FLAG_HASH = 1 << 3,
	FLAG_PLUS = 1 << 4,
	FLAG_SPACE = 1 << 5,
	FLAG_PAST = 1 << 6,
	FLAG_DAST = 1 << 7,
}					t_flags;

/**
 * @brief  This is structer that contain information about
 *     current formating symbol.
 */
typedef struct s_format
{
	char			format;
	t_datatype		type;
	int				precision;
	int				width;
	int				is_past_reverce;
	unsigned int	flags;
}					t_format;

#endif