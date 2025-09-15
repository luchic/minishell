

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

char	*get_cmd_path(char *cmd_name, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*cmd_path;
	int		i;

	if (!cmd_name || !envp || !getenv("PATH"))
		return (NULL);
	paths = ft_split(getenv("PATH"), ':'); // malloc
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/"); // malloc
		if (!tmp)
			return (free_str_array(paths), NULL);
		cmd_path =  ft_strjoin(tmp, cmd_name); // malloc
		if (!cmd_path)
			return (free(tmp), free_str_array(paths), NULL);
		free(tmp);
		if (!cmd_path)
			return (free_str_array(paths), NULL);
		if (access(cmd_path, F_OK) == 0)
			return (free_str_array(paths), cmd_path);
		free(cmd_path);
	}
	return (free_str_array(paths), NULL);
}
