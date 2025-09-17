
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"
# include "ft_common.h"

char	**handle_assignments(t_minishell *mnsh, t_list *assignments)
{
	t_list	*current;
	char	**original_env;
	char	*arg;

	current = assignments;
	original_env = ft_strdup_array(mnsh->envp);
	if (!original_env)
		return (NULL);
	while (current)
	{
		if (!is_valid_identifier(current->content) || !ft_strchr(current->content, '='))
		{
			ft_printf_fd(STDERR, "minishell: assignment: `%s': not a valid identifier\n", current->content);
			current = current->next;
			continue ;
		}
		arg = current->content;
		if (ft_strchr(arg, '='))
			update_env_var(arg, &(mnsh->envp));
		current = current->next;
	}
	return (original_env);
}
