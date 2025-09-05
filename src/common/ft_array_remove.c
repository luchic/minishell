
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"

void	ft_array_remove(char ***array, char *value)
{
	int		i;
	int		j;
	char	**new_array;

	if (!array || !*array || !value)
		return ;
	i = 0;
	while ((*array)[i] && ft_strncmp((*array)[i], value, ft_strlen(value)) != 0)
		i++;
	if (!(*array)[i])
		return ; // value not found
	new_array = malloc(sizeof(char *) * (ft_array_size(*array))); // -1 +1 for NULL
	if (!new_array)
		return ;
	j = 0;
	i = 0;
	while ((*array)[i])
	{
		if (ft_strncmp((*array)[i], value, ft_strlen(value)) != 0)
		{
			new_array[j] = (*array)[i];
			j++;
		}
		else
			free((*array)[i]); // free the removed element
		i++;
	}
	new_array[j] = NULL;
	free(*array);
	*array = new_array;
}
