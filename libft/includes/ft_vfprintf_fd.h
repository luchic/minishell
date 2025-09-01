/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_fd.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:14:40 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/22 15:55:46 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VFPRINTF_FD_H
# define FT_VFPRINTF_FD_H

# include <stdarg.h>

/**
 * @brief  Interface for formatted output to a file descriptor.
 * @note   It's the internal function that processes the format string
 * @param  ap: Argument list containing the values to format.
 * @param  format:  
 * @param  fd: 
 * @retval 
 */
int	ft_vfprintf_fd(va_list ap, const char *format, int fd);

#endif