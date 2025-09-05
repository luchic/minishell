
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"


char	**ft_array_append(char **arr, char *str)
{
	char	**new_arr;
	int		counts;
	int		i;

	counts = 0;
	if (arr)
		counts = count_args(arr);
	new_arr = malloc(sizeof(char *) * (counts + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < counts)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	if (arr)
		free(arr);
	return (new_arr);
}
