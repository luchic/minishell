

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_subshell(t_minishell *mnsh, t_subshell *subsh)
{
	if (!mnsh || !subsh || !subsh->script)
		return (1);
	if (preprocess_heredoc_node(subsh->script) != EXIT_SUCCESS)
	{
		mnsh->last_exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (execute_script(mnsh, subsh->script));
}
