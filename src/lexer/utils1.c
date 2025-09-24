int	is_ifs_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

void	skip_ifs_spaces(const char **p)
{
	while (is_ifs_space((unsigned char)**p))
		(*p)++;
}
