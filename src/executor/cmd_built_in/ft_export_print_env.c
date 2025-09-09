
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"


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
	int		j;
	char	*tmp;

	sorted = array_dup(envp);
	if (!sorted)
		return ;
	array_bubble_sort(&sorted);
	i = 0;
	while (sorted[i])
	{
		ft_printf_fd(fd, "declare -x '%s'\n", sorted[i]);
		i++;
	}
	free_str_array(sorted);
}
