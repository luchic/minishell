

#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

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

static int	create_heredoc_file(const char *delimiter, char **fname)
{
	char	*temp_filename;
	int		status;
	int		temp_fd;

	temp_filename = create_heredoc_namefile();
	if (!temp_filename)
		return (EXIT_FAILURE);
	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR, "heredoc: cannot create temp file\n");
		free(temp_filename);
		return (EXIT_FAILURE);
	}
	status = save_data_heredoc((char *)delimiter, temp_fd);
	close(temp_fd);
	if (status)
	{
		unlink(temp_filename);
		free(temp_filename);
		return (status);
	}
	*fname = temp_filename;
	return (0);
}

int	preprocess_heredocs_fds(t_redirection *redir)
{
	char		*filename;
	int			status;
	t_minishell	*mnsh;

	filename = NULL;
	mnsh = *get_mnsh();
	status = create_heredoc_file(redir->value, &filename);
	if (status != 0)
	{
		mnsh->last_exit_status = status;
		return (status);
	}
	free(redir->value);
	redir->value = filename;
	return (EXIT_SUCCESS);
}
