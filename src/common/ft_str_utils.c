/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:48:52 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/20 11:51:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_append_str(char **dest, const char *src)
{
	char	*new_str;

	if (!dest || !src)
		return (-1);
	if (!*dest)
		new_str = ft_strdup(src);
	else
		new_str = ft_strjoin(*dest, src);
	if (!new_str)
		return (-1);
	free(*dest);
	*dest = new_str;
	return (0);
}

char	*ft_insert(char *str, char *insert, int pos)
{
	char	*new_str;
	int		len_str;
	int		len_insert;

	if (!str || !insert || pos < 0)
		return (NULL);
	len_str = ft_strlen(str);
	len_insert = ft_strlen(insert);
	if (pos > len_str)
		pos = len_str;
	new_str = ft_calloc(len_str + len_insert + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, pos);
	ft_memcpy(new_str + pos, insert, len_insert);
	ft_memcpy(new_str + pos + len_insert, str + pos, len_str - pos);
	return (new_str);
}

char	*ft_replace(char *str, char *insert, int pos, int end)
{
	char	*new_str;
	int		len_str;
	int		len_insert;

	end += 1;
	if (!str || !insert || pos < 0 || end < pos)
		return (NULL);
	len_str = ft_strlen(str);
	if (len_str < end)
		end = len_str;
	if (len_str < pos)
		pos = len_str;
	len_insert = ft_strlen(insert);
	new_str = ft_calloc(len_str - (end - pos) + len_insert + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, pos);
	ft_memcpy(new_str + pos, insert, len_insert);
	ft_memcpy(new_str + pos + len_insert, str + end, len_str - end);
	return (new_str);
}
