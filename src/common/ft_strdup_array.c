/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:09:16 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 09:09:19 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"

/*
** Duplicates an array of strings.
** Returns a newly allocated array of duplicated strings.
** The returned array is NULL-terminated.

*/

char	**ft_strdup_array(char **array)
{
	int		count;
	char	**dup_array;
	int		i;

	count = 0;
	while (array && array[count])
		count++;
	dup_array = malloc((count + 1) * sizeof(char *));
	if (!dup_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup_array[i] = ft_strdup(array[i]);
		if (!dup_array[i])
			return (free_str_array(dup_array), NULL);
		i++;
	}
	dup_array[count] = NULL;
	return (dup_array);
}
