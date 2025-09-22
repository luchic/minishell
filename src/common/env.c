
#include "ft_defines.h"
#include "libft.h"

static char	*get_internal_env(t_minishell *mnsh, const char *name)
{
	t_var	*vars;

	if (!mnsh || !name || !mnsh->variables)
		return (NULL);
	vars = mnsh->variables;
	while (vars)
	{
		if (vars && ft_strcmp(vars->name, name) == 0)
			return (ft_strdup(vars->value));
		vars = vars->next;
	}
	return (NULL);
}

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
	return (get_internal_env(mnsh, name));
}
