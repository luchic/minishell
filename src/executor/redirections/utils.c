
#include "ft_common.h"
#include "ft_defines.h"
#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	char		*line;
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh)
		return (NULL);
	if (mnsh->is_tty_in)
		return (readline("> "));
	else
		line = get_next_line(STDIN);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}
