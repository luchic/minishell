/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:02:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/26 17:41:48 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_a_line(int fd, char *chunk)
{
	char	*vault;
	int		bytes_read;
	char	*temp;

	vault = ft_strjoin(chunk, "");
	if (!vault)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(vault, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(vault), NULL);
		if (bytes_read == 0)
			break ;
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(vault, chunk);
		if (!temp)
			return (free(vault), NULL);
		free(vault);
		vault = temp;
	}
	return (vault);
}

static char	*to_line(char *vault)
{
	size_t	i;
	char	*the_line;

	if (!vault || !*vault)
		return (NULL);
	i = 0;
	while (vault[i] && vault[i] != '\n')
		i++;
	if (vault[i] == '\n')
		i++;
	the_line = ft_substr_gnl(vault, 0, i);
	if (!the_line)
		return (NULL);
	return (the_line);
}

static void	update(char *chunk)
{
	char	*chars_read;

	chars_read = ft_strchr(chunk, '\n');
	if (!chars_read)
	{
		chunk[0] = '\0';
		return ;
	}
	chars_read++;
	if (*chars_read == '\0')
	{
		chunk[0] = '\0';
		return ;
	}
	ft_memmove(chunk, chars_read, ft_strlen(chars_read) + 1);
}

char	*get_next_line(int fd)
{
	static char	chunk[BUFFER_SIZE + 1];
	char		*vault;
	char		*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	vault = read_a_line(fd, chunk);
	if (!vault)
		return (chunk[0] = '\0', NULL);
	the_line = to_line(vault);
	free(vault);
	if (!the_line)
		return (chunk[0] = '\0', NULL);
	if (the_line[0] == '\0')
		return (free(the_line), chunk[0] = '\0', NULL);
	update(chunk);
	return (the_line);
}

/* #include <string.h>

void	leak()
{
	system("leaks -q a.out");
}

void gnl(int fd, char *expected)
{
	char *line = get_next_line(fd);
	if (line == NULL && expected == NULL)
		return;
	if (line != NULL && expected != NULL && strcmp(line, expected) == 0)
	{
		printf("Test passed: %s\n", line);
		free(line);
		return;
	}
	printf("Test failed: expected '%s', got '%s'\n", expected, line ?
		line : "NULL");
} */
