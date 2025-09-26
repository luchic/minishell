
#include "ft_common.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}
