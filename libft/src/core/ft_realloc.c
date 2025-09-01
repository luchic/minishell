/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:28:07 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/10 21:33:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;
	char	*str;
	size_t	copy_size;

	if (ptr == NULL)
		return (ft_calloc(new_size, sizeof(char)));
	if (new_size == 0)
		return (free(ptr), NULL);
	str = (char *)ptr;
	new_ptr = (char *)ft_calloc(new_size, sizeof(char));
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, str, copy_size);
	free(ptr);
	return (new_ptr);
}
