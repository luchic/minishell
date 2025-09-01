/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:50:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/22 15:59:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTER_H
# define FT_PRINTER_H

# include "ft_defs.h"
# include <stdarg.h>

/**
 * @brief  Prints the formatted output based on the current format
 * @details This function handles the printing of various data types
 *          according to the specified format in the t_format structure.
 * @param  cur: Current format structure containing the format specifications. 
 * @param  ap: Argument list containing the values to format.
 * @param  fd: File descriptor to which the output will be printed.
 * @retval The number of characters printed, or -1 on error.
 */
int	ft_print_format(t_format *cur, va_list ap, int fd);

/**
 * @brief  Prints a integer value according to the specified format.
 * @param  ap: argument list containing the integer to print.
 * @param  cur: Current format structure containing the format specifications.
 * @param  fd: File descriptor to which the output will be printed.
 * @retval The number of characters printed, or -1 on error.
 */
int	ft_print_int(va_list ap, t_format *cur, int fd);

/**
 * @brief  Prints an unsigned integer value according to the specified format.
 * @param  ap: argument list containing the unsigned integer to print.
 * @param  cur: Current format structure containing the format specifications.
 * @param  fd: File descriptor to which the output will be printed.
 * @retval The number of characters printed, or -1 on error.
 */
int	ft_print_unit(va_list ap, t_format *cur, int fd);

/**
 * @brief  Prints a string according to the specified format.
 * @param  ap: argument list containing the string to print.
 * @param  cur: Current format structure containing the format specifications.
 * @param  fd: File descriptor to which the output will be printed.
 * @retval The number of characters printed, or -1 on error.
 */
int	print_str(va_list ap, t_format *cur, int fd);

/**
 * @brief  Prints a pointer according to the specified format.
 * @param  ap: argument list containing the pointer to print.
 * @param  cur: Current format structure containing the format specifications.
 * @param  fd: File descriptor to which the output will be printed.
 * @retval The number of characters printed, or -1 on error.
 */
int	ft_print_ptr(va_list ap, t_format *cur, int fd);

#endif