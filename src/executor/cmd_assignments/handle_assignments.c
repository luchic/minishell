
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

char	**handle_assignments(t_minishell *mnsh, t_list *assignments)
{
	t_list			*current;
	t_assignment	*asgmt;
	char			**original_env;

	current = assignments;
	original_env = ft_strdup_array(mnsh->envp);
	if (!original_env)
		return (NULL);
	while (current)
	{
		asgmt = (t_assignment *)current->content;
		if (!is_valid_identifier(asgmt->value) || !ft_strchr(asgmt->value, '='))
		{
			ft_printf_fd(STDERR,
				"minishell: assignment: `%s': not a valid identifier\n",
				asgmt->value);
			current = current->next;
			continue ;
		}
		if (ft_strchr(asgmt->value, '='))
			update_env_var(asgmt->value, &(mnsh->envp));
		current = current->next;
	}
	return (original_env);
}
