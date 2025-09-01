/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:39:25 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/15 15:18:52 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substr(char const *s, char c)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (*s)
	{
		if (*s != c && check == 0)
		{
			check = 1;
			i++;
		}
		else if (*s == c)
			check = 0;
		s++;
	}
	return (i);
}

static size_t	substr_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

static char	*get_substr(const char *s, char c)
{
	char	*substr;
	size_t	j;
	size_t	len;

	len = substr_len(s, c);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	j = 0;
	while (s[j] && j < len)
	{
		substr[j] = s[j];
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

static void	*free_rest(char **arr, int i)
{
	if (!arr[i])
	{
		while (i--)
		{
			free(arr[i]);
		}
		free(arr);
		return (NULL);
	}
	else
		return (arr[i]);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;

	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (count_substr(s, c) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			ptr[i] = get_substr(s, c);
			if (!ptr[i])
				return (free_rest(ptr, i), NULL);
			s = s + substr_len(s, c);
			i++;
		}
		else
			s++;
	}
	ptr[i] = NULL;
	return (ptr);
}

/* int	main(void)
{
	char const	*s1 = "hello!";
	// char		c = 32:' ';
	char		**ptr;
	int			i = 0;

	ptr = ft_split(s1, ' ');
	while (ptr[i] != NULL)
	{
		printf("%s\n", ptr[i]);
		i++;
	}
	while (i - 1 >= 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
	return (0);
} */
