/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:12:04 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/13 18:29:17 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char ch, char const *set)
{
	while (*set)
	{
		if (*set == ch)
			return (1);
		set++;
	}
	return (0);
}

static char	*empty_string(void)
{
	return (ft_strdup(""));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	char const	*start;
	char const	*end;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (empty_string());
	while (check_set(*s1, set) && *s1)
		s1++;
	start = s1;
	if (*start == '\0')
		return (empty_string());
	while (*s1)
		s1++;
	while (check_set(*(s1 - 1), set) && s1 - 1 != start)
		s1--;
	end = s1;
	res = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy((void *)res, (void *)start, end - start);
	return (res);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *s1 = 
//"   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";
// 	char *s2 = "Hello \t  Please\n Trim me !";

// 	char *res = ft_strtrim(s1, " \n\t");
// 	printf("Strtrim: '%s'\n", res);
// 	if(!strcmp(s2, res))
// 		printf( "Test passed: Strtrim result is correct.\n" );
// 	else
// 		printf( "Test failed: Strtrim
// result is incorrect. Expected: '%s', Got: '%s'\n" , s2, res);
// 	printf("Strtrim: '%d'\n", res[strlen(res)]);
// }