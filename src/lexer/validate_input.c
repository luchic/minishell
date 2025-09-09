
static int	is_valid(const char *input)
{
	int	parentheses;

	parentheses = 0;
	while (*input)
	{
		if (*input == '(')
			parentheses++;
		else if (*input == ')')
			parentheses--;
		if (parentheses < 0)
			return (0);
		input++;
	}
	return (parentheses == 0);
}

int	validate_parantheses(const char *input)
{
	return (is_valid(input));
}