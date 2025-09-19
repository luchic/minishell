
#include "ft_defines.h"
#include "libft.h"

char	*get_env(t_minishell *mnsh, const char *name)
{
	char	**env;

	if (!mnsh || !name || !mnsh->envp)
		return (NULL);
	env = mnsh->envp;
	while (*env)
	{
		if (ft_strncmp(*env, name, ft_strlen(name)) == 0
			&& (*env)[ft_strlen(name)] == '=')
			return (ft_strdup(*env + ft_strlen(name) + 1));
		env++;
	}
	return (NULL);
}
