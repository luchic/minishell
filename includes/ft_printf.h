/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:43:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/12 11:26:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

typedef enum e_log_level
{
	LOG_DEBUG = 0,
	LOG_INFO = 1,
	LOG_WARNING = 2,
	LOG_ERROR = 3,
	LOG_CRITICAL = 4
}	t_log_level;

# ifndef DEFLOG_LEVEL
#  define DEFLOG_LEVEL LOG_ERROR
# endif

/**
 * @brief The replica of the printf function from the C standard library.
 * This function formats and prints a string to the standard output.
 * @param  format: The format string that specifies how to format the output.
 * @retval The number of characters printed. -1 if an error occurs.
 */
int	ft_printf(const char *format, ...);

/**
 * @brief The replica of the printf function from the C standard library.
 * This function formats and prints a string to the specified file descriptor.
 * @param  fd: The file descriptor to which the output will be written.
 * @param  format: The format string that specifies how to format the output.
 * @retval The number of characters printed. -1 if an error occurs.
 */
int	ft_printf_fd(int fd, const char *format, ...);

/**
 * @brief Logs a message to the specified file descriptor with a
 * specific log level.
 * @param level The log level of the message.
 * @param fd The file descriptor to which the log message will be written.
 * @param format The format string for the log message.
 * @param ... The values to be formatted and included in the log message.
 * @return int The number of characters written, or -1 on error.
 */
int ft_log_fd(t_log_level level, int fd, const char *format, ...);
#endif