
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static char	**array_dup(char **en)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = ft_calloc(count_args(en) + 1, sizeof(char *));
	if (!sorted)
		return (NULL);
	while (en[i])
	{
		sorted[i] = ft_strdup(en[i]);
		if (!sorted[i])
			return (free_str_array(sorted), NULL);
		i++;
	}
	sorted[i] = NULL;
	return (sorted);
}

void	array_bubble_sort(char ***sorted)
{
	int		i;
	int		j;
	char	*tmp;
	int		n;

	n = count_args(*sorted);
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp((*sorted)[j], (*sorted)[j + 1]) > 0)
			{
				tmp = (*sorted)[j];
				(*sorted)[j] = (*sorted)[j + 1];
				(*sorted)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export_print_env(char **envp, int fd)
{
	char	**sorted;
	int		i;
	char	*name;
	char	*value;

	sorted = array_dup(envp);
	if (!sorted)
		return ;
	array_bubble_sort(&sorted);
	i = -1;
	while (sorted[++i])
	{
		if (ft_strchr(sorted[i], '='))
		{
			name = ft_substr(sorted[i], 0, ft_strchr(sorted[i], '=')
					- sorted[i]);
			value = ft_strdup(ft_strchr(sorted[i], '=') + 1);
			ft_printf_fd(fd, "declare -x %s=\"%s\"\n", name, value);
			free(name);
			free(value);
		}
		else
			ft_printf_fd(fd, "declare -x %s\n", sorted[i]);
	}
	free_str_array(sorted);
}
