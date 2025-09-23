
// return exit status of the subshell execution
/*
all executions happen in the child process
*/

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_subshell(t_minishell *mnsh, t_subshell *subsh)
{
	if (!mnsh || !subsh || !subsh->script)
		return (1);
	return (execute_script(mnsh, subsh->script));	
}
