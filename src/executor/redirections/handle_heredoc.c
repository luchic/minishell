/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:53:48 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 12:08:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	ft_is_limiter(char *line, char *del)
{
	char	*tmp;

	if (!line)
		return (1);
	if (ft_strchr(line, '\n'))
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		tmp = ft_strdup(line);
	if (!tmp)
		return (1);
	if (del[0] != '\0' && !ft_strcmp(tmp, del))
		return (free(tmp), 1);
	if (del[0] == '\0' && (!ft_strcmp(tmp, "\n") || !ft_strcmp(tmp, "")))
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

char	*get_next_line_not_in_tty(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	ft_write_data_to_std(char *del, int fd)
{
	char		*line;
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	while (1)
	{	
		if (mnsh->is_tty_in)
			line = readline("> ");
		else
			line = get_next_line_not_in_tty();
		if (ft_is_limiter(line, del))
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)
		{
			ft_printf_fd(STDERR, "\nminishell: warning: here-document delimited by \
				end-of-file (wanted `%s')\n", del);
			break ;
		}
		(ft_printf_fd(fd, "%s\n", line), free(line));
	}
}

static char	*create_heredoc_namefile(void)
{
	static unsigned int	counter;
	char				*filename;
	char				*num_str;

	counter = 0;
	num_str = ft_itoa(counter++);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (filename);
}

static char	*create_heredoc_file(const char *delimiter)
{
	char	*temp_filename;
	int		temp_fd;

	temp_filename = create_heredoc_namefile();
	if (!temp_filename)
		return (NULL);
	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR, "heredoc: cannot create temp file\n");
		free(temp_filename);
		return (NULL);
	}
	ft_write_data_to_std((char *)delimiter, temp_fd);
	close(temp_fd);
	if (temp_fd == -1)
	{
		free(temp_filename);
		ft_printf_fd(STDERR, "heredoc: cannot open temp file for reading\n");
		return (NULL);
	}
	return (temp_filename);
}

int	preprocess_heredocs_fds(t_redirection *redir)
{
	char	*filename;

	filename = create_heredoc_file(redir->value);
	if (!filename)
		return (EXIT_FAILURE);
	free(redir->value);
	redir->value = filename;
	return (EXIT_SUCCESS);
}
