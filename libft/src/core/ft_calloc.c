/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:44:35 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/14 09:27:43 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	total;

	if ((count && size > ULONG_MAX / count))
		return (NULL);
	total = count * size;
	res = malloc(total);
	if (!res)
		return (NULL);
	ft_memset(res, 0, total);
	return (res);
}

/* #include <stdio.h>
int main()
{
	void	*ptr;

	ptr = NULL;
	printf("Current ptr: %p\n", ptr);
	ptr = ft_calloc(0, sizeof(int));
	printf("Afte calloc ptr: %p\n", ptr);
	free(ptr);
} */