/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:38:47 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 13:37:51 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

/**
 * @brief  Find the first occurrence of a character in a string.
 * @param  s: String to search in. 
 * @param  c: Character to search for. 
 * @retval Pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found.
 */
char		*ft_strchr(const char *s, int c);

#endif