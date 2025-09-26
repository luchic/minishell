
#include "libft.h"
#include "ft_common.h"

int	append_char(char **dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (ft_append_str(dst, buf));
}

int	is_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
