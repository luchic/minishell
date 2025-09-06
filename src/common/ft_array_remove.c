
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"

void	ft_array_remove(char ***array, char *value)
{
	int		i;
	int		j;
	char	**envp;
	char	**new_array;

	if (!array || !*array || !value)
		return ;
	i = 0;
	envp = *array;
	// find if value exists in envp
	while (envp[i] && ft_strncmp(envp[i], value, ft_strlen(value)) != 0)
		i++;
	if (!envp[i])
		return ; // value not found
	new_array = malloc(sizeof(char *) * (get_array_counts(envp) + 1)); // +1 for NULL terminator
	if (!new_array)
		return ;
	j = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], value, ft_strlen(value)) != 0)
		{
			new_array[j] = envp[i];
			j++;
		}
		else
			free(envp[i]); // free the removed element
		i++;
	}
	new_array[j] = NULL;
	free(envp);
	*array = new_array;
}
