
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int	ft_is_limiter(char *line, char *del)
{
	char	*tmp;

	if (!line)
		return (1);
	if (ft_strchr(line, '\n'))
		line[ft_strlen(line) - 1] = '\0';
	if (!tmp)
		return (1);
	if (del[0] != '\0' && !ft_strcmp(tmp, del))
		return (free(tmp), 1);
	if (del[0] == '\0' && (!ft_strcmp(tmp, "\n") || !ft_strcmp(tmp, "")))
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

void	ft_write_data_to_std(char *del, int fd)
{
	char	*line;

	while (1)
	{
		ft_printf_fd(STDERR, "> ");  // heredoc prompt
		line = get_next_line(STDIN_FILENO);
		if (ft_is_limiter(line, del))
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)  // EOF reached (Ctrl+D)
		{
			ft_printf_fd(STDERR, "\nminishell: warning: here-document delimited by end-of-file (wanted `%s')\n", del);
			break ;
		}
		ft_printf_fd(fd, "%s", line);
		free(line);
	}
}

static char	*create_heredoc_tempfile(void)
{
	static unsigned int	counter = 0;
	char		*filename;
	char		*num_str;

	num_str = ft_itoa(counter++);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (filename);
}

int	handle_heredoc(t_redirection *redir, t_command *cmd)
{
	char	*temp_filename;
	int		temp_fd;
	char	*line;
	char	*delimiter;

	temp_filename = create_heredoc_tempfile();
	if (!temp_filename)
		return (0);

	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR, "heredoc: cannot create temp file\n");
		free(temp_filename);
		return (0);
	}

	delimiter = redir->value;
	ft_write_data_to_std(delimiter, temp_fd);
	close(temp_fd);

	// Open temp file for reading
	temp_fd = open(temp_filename, O_RDONLY);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR, "heredoc: cannot open temp file for reading\n");
		unlink(temp_filename);
		free(temp_filename);
		return (0);
	}

	if (cmd->fd_in != STDIN && cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = temp_fd;

	// Clean up temp file (it will be deleted when fd is closed)
	unlink(temp_filename);
	free(temp_filename);

	return (1);
}
