/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:24:52 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/30 16:40:14 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Function converts the initial portion of the string
 * pointed to by str to int representation.
 * @param  str: String converting to int.
 * @retval The converted value or 0 on error.
 */
double				ft_atof(const char *str);

/**
 * @brief Function converts the initial portion of the string
 * pointed to by str to int representation.
 * @param  str: String converting to int.
 * @retval The converted value or 0 on error.
 */
int					ft_atoi(const char *str);

/**
 * @brief The bzero() function writes n zeroed bytes to the string s.
 * If n is zero, bzero() does nothing.
 * @param  s: Pointer to location.
 * @param  n: Number of bytes, that will be erase with zero.
 * @retval None
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief The function shall allocate unused space for an array of
 *     count elements each of whose size in bytes is size.  The space
 *     shall be initialized to all bits 0.
 * @param  count: Number of elements in array.
 * @param  size: Size of every element in array.
 * @retval void pointer to block of memory.
 */
void				*ft_calloc(size_t count, size_t size);

/**
 * @brief  This function attempts to reallocate the memory block pointed to by
 *   ptr that was previously allocated with malloc(), calloc() or realloc().
 *   The previsous memory is freed.
 *   The new size of the memory block is specified by new_size.
 * @note   If ptr is NULL, the function behaves like malloc() and allocates
 *   a new memory block of size new_size.
 *   If malloc() fails to allocate the requested memory, the function returns
 *   NULL and the original memory doesn't freed and remains allocated.
 * @param  ptr: The pointer to the previously allocated memory block.
 * @param  old_size: The size of the previously allocated memory block.
 * @param  new_size: The new size of the memory block to be allocated.
 * @retval Pointer to the newly allocated memory block.
 */
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/**
 * @brief Check if character is alpha or digit.
 * @param  c: Character that will be checked.
 * @retval Return 1 if alpha or digit, another case - 0.
 */
int					ft_isalnum(int c);

/**
 * @brief	Check if character is alpha.
 * @param  c: Currect character.
 * @retval Returns zero if the character tests false and returns non-zero
 * if the character tests true.
 */
int					ft_isalpha(int c);

/**
 * @brief  Function tests for an ASCII character, which is any
 * character between 0 and octal 127 inclusive.
 * @param  c: Current character.
 * @retval Returns zero if the character not ascii and returns non-zero
 * if the character is ascii.
 */
int					ft_isascii(int c);

/**
 * @brief  Check if character is a digit.
 * @param  c: Current character.
 * @retval Return zero if character not digit in another case return non-zero.
 */
int					ft_isdigit(int c);

/**
 * @brief Check if character is printable. Printable is 32 (sp) - 126 (~).
 * @param  c: Current character.
 * @retval Return zero if character is not printable
 */
int					ft_isprint(int c);

/**
 * @brief  Check if character is lowercase.
 * @param  c: Current character.
 * @retval Return 1 if character is lowercase othewise 0.
 */
int					ft_islower(int c);

/**
 * @brief  Check if character is uppercase.
 * @param  c: Current character.
 * @retval Return 1 if character is uppercase othewise 0.
 */
int					ft_isupper(int c);

/**
 * @brief  The function looking for the first occurrence of c
 * (converted to an unsigned char) in string s.
 * @param  s: Pointer to the block of memory.
 * @param  c: Looking for character.
 * @param  n: Number of checking bytes.
 * @retval The function returns a pointer to the byte looking for,
 * or NULL if no such byte exists.
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief  The function compares byte string s1 against byte string s2.
 * Both strings are assumed to be n bytes long.
 * @param  s1: First block of memory.
 * @param  s2: Second block of memory.
 * @param  n: Number of compared bytes.
 * @retval The function returns zero if the two strings are identical,
 *   otherwise returns the difference between the first two differing bytes
 *   (treated as unsigned char values, so that `\200' is greater
 *   than `\0', for example). Zero-length strings are always identical.
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief  The ft_memcpy() function copies n bytes from memory area
 *   src to memory area dst. If dst and src overlap, behavior is undefined.
 *   Applications in which dst and src might overlap should
 *   use ft_memmove() instead.
 * @param  dst: Pointer to destination block of memory.
 * @param  src: Pointer to block memory from will be copied data.
 * @param  n: Number of copied bytes.
 * @retval The ft_memcpy() function returns the original value of dst.
 */
void				*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief  The ft_memmove() function copies len bytes from string src to
 *   string dst.  The two strings may overlap; the copy is always done
 *   in a non-destructive manner.
 * @param  dst: Pointer to destination block of memory.
 * @param  src: Pointer to block memory from will be copied data.
 * @param  len: Number of copied bytes.
 * @retval The ft_memmove() function returns the original value of dst.
 */
void				*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief  The ft_memset() function writes len bytes of value c
 *   (converted to an unsigned char) to the string b.
 * @param  b: Point to memory block, that will be setuppad.
 * @param  c: New value.
 * @param  len: The number of overwritten bytes.
 * @retval The ft_memset() function returns its first argument.
 */
void				*ft_memset(void *b, int c, size_t len);

/**
 * @brief  The ft_strchr() function locates the first occurrence of c
 *   (converted to a char) in the string pointed to by s.
 *   The terminating null character is considered to be part of the string;
 *   therefore if c is `\0', the functions locate the terminating `\0'.
 * @param  s: Pointer to the string.
 * @param  c: Character that we looking for.
 * @retval  The functions ft_strchr() return a pointer to the located
 *   character, or NULL if the character does not appear in the string.
 */
char				*ft_strchr(const char *s, int c);

/**
 * @brief  The ft_strdup() function allocates sufficient memory for a copy
 *   of the string s1, does the copy, and returns a pointer to it.
 *   The pointer may subsequently be used as an argument to the function
 *   free().
 * @param  s1: String that will be copied.
 * @retval Return pointer to the new string.
 */
char				*ft_strdup(const char *s1);

/**
 * @brief  The ft_strlcat() functions concatenate strings with the same
 *   input parameters. ft_strlcat() take the full size of the destination
 *   buffer and guarantee NUL-termination if there is room.
 *   Note that room for the NUL should be included in dstsize.
 *
 *   ft_strlcat() appends string src to the end of dst.  It will append
 *   at most dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate,
 *   unless dstsize is 0 or the original dst string was longer than dstsize
 *   (in practice this should not happen as it means that either dstsize is
 *   incorrect or that dst is not a proper string).
 *
 *  If the src and dst strings overlap, the behavior is undefined.
 * @param  dest: Original string.
 * @param  src: Concatenated string.
 * @param  dstsize: Size of destination buffer.
 * @retval The ft_strlcat() function return the total length of the string
 *   they tried to create. For ft_strlcat() that means the initial length
 *   of dst plus the length of src.
 *
 *   If the return value is >= dstsize, the output string has been truncated.
 *   It is the caller's responsibility to handle this.
 */
size_t				ft_strlcat(char *dest, const char *src, size_t dstsize);

/**
 * @brief  The ft_strlcpy() functions copy strings with the same
 *   input parameters. ft_strlcat() take the full size of the destination
 *   buffer and guarantee NUL-termination if there is room.
 *   Note that room for the NUL should be included in dstsize.
 *
 *   ft_strlcpy() copies up to dstsize - 1 characters from the string src
 * 		to dst, NUL-terminating the result if dstsize is not 0.
 *
 *   If the src and dst strings overlap, the behavior is undefined.
 * @param  dest: Original string.
 * @param  src: Copied string.
 * @param  dstsize: Size of destination buffer.
 * @retval The ft_strlcpy() function return the total length of the string
 *   they tried to create. For ft_strlcpy() that means the length of src.
 *
 *   If the return value is >= dstsize, the output string has been truncated.
 *   It is the caller's responsibility to handle this.
 */
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);

/**
 * @brief  The ft_strlen() function computes the length of the string s.
 * @param  s: The string.
 * @retval Return the length of string.
 */
size_t				ft_strlen(const char *s);

/**
 * @brief  The ft_strncmp() function compares not more than n characters.
 * @param  s1: First string.
 * @param  s2: Second string.
 * @param  n: The number of characters that will be compared.
 * @retval The ft_strncmp() function return an integer greater than,
 *   equal to, or less than 0, according as the string s1 is greater than,
 *   equal to, or less than the string s2.  The comparison is done using
 *   unsigned characters, so that `\200' is greater than `\0'.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief  The ft_strcmp() function compares the two strings s1 and s2.
 *   The ft_strcmp() function returns an integer greater than, equal to,
 *   or less than 0, according as the string s1 is greater than, equal to,
 *   or less than the string s2.  The comparison is done using unsigned
 *   characters, so that `\200' is greater than `\0'.
 * @param  s1: First string.
 * @param  s2: Second string.
 * @retval The ft_strcmp() function return an integer greater than,
 *   equal to, or less than 0.
 */
int					ft_strcmp(const char *s1, const char *s2);

/**
 * @brief  The ft_strnstr() function locates the first occurrence of
 *   the null-terminated string needle in the string haystack, where not
 *   more than len characters are searched.
 *   Characters that appear after a `\0' character are not searched.
 * @param  haystack: String where looking for needle.
 * @param  needle: Substring that we looking for.
 * @param  len: The max number of characters that we searched.
 * @retval If needle is an empty string, haystack is returned; if needle
 *  occurs nowhere in haystack, NULL is returned; otherwise a pointer
 *  to the first character of the first occurrence of needle is returned.
 */
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

/**
 * @brief  The ft_strrchr() function locates the last occurrence of c (converted
 *  to a char) in the string pointed to by s.  The terminating null character is
 *  considered to be part of the string; therefore if c is `\0',
 *  the functions locate the terminating `\0'.
 * @param  s: String where looking for character.
 * @param  c: Character that we looking for.
 * @retval  The functions ft_strrchr() return a pointer to the located
 * character, or NULL if the character does not appearing the string.
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @brief  The ft_tolower() function converts an upper-case letter to the
 *  corresponding lower-case letter.  The argument must be representable as
 *  an unsigned char or the value of EOF.
 * @param  c: Character that will be tried to convert to lowercase.
 * @retval If the argument is an upper-case letter, the tolower() function
 *  returns the corresponding lower-case letter if there is one; otherwise,
 *  the argument is returned unchanged.
 */
int					ft_tolower(int c);

/**
 * @brief  The ft_toupper() function converts a lower-case letter to
 *  the corresponding upper-case letter.  The argument must be representable
 *  as an unsigned char or the value of EOF.
 * @param  c: Character that will be tried to convert to uppercase.
 * @retval If the argument is a lower-case letter, the ft_toupper() function
 *  returns the corresponding upper-case letter if there is one;
 *  otherwise, the argument is returned unchanged.
 */
int					ft_toupper(int c);

/**
 * @brief  	Allocates memory (using malloc(3)) and returns a
 *			substring from the string ’s’.
 *			The substring starts at index ’start’ and has a
 *			maximum length of ’len’.
 * @param  s: The original string from which to create the substring.
 * @param  start: The starting index of the substring within ’s’.
 * @param  len: The maximum length of the substring.
 * @retval 	The substring.
 *			NULL if the allocation fails.
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief  Allocates memory (using malloc(3)) and returns a new string,
 *  which is the result of concatenating ’s1’ and ’s2’.
 * @param  s1: The prefix string.
 * @param  s2: The suffix string.
 * @retval The new string. NULL if the allocation fails.
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief  Allocates memory (using malloc(3)) and returns a copy
 *  of ’s1’ with characters from ’set’ removed from the beginning and the end.
 * @note
 * @param  s1: The string to be trimmed.
 * @param  set: The string containing the set of characters to be removed.
 * @retval The trimmed string. NULL if the allocation fails.
 */
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief  Allocates memory (using malloc(3)) and returns an array of strings
 *  obtained by splitting ’s’ using the character ’c’ as a delimiter.
 *  The array must end with a NULL pointer.
 * @param  s: The string to be split.
 * @param  c: The delimiter character.
 * @retval The array of new strings resulting from the split.
 *  NULL if the allocation fails.
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Allocates memory (using malloc(3)) and returns a string representing
 *  the integer received as an argument. Negative numbers must be handled.
 * @param  n: The integer to convert.
 * @retval The string representing the integer. NULL if the allocation fails.
 */
char				*ft_itoa(int n);

/**
 * @brief  Applies the function f to each character of the string s, passing
 *  its index as the first argument and the character itself as the second.
 *  A new string is created (using malloc(3)) to store the results from
 *  the successive applications of f.
 * @param  s: The string to iterate over.
 * @param  f: The function to apply to each character.
 * @retval The string created from the successive applications of ’f’.
 *  Returns NULL if the allocation fails.
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief  Applies the function ’f’ to each character of the string passed
 *  as argument, passing its index as the first argument. Each character
 *  is passed by address to ’f’ so it can be modified if necessary.
 * @param  s: The string to iterate over.
 * @param  f: The function to apply to each character.
 * @retval None.
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief  Outputs the character ’c’ to the specified file descriptor.
 * @param  c:  The character to output.
 * @param  fd: The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putchar_fd(char c, int fd);

/**
 * @brief  Outputs the string ’s’ to the specified file descriptor.
 * @param  s: The string to output.
 * @param  fd: The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putstr_fd(char *s, int fd);

/**
 * @brief  Outputs the n first characters of string ’s’
 *  to the specified file descriptor.
 * @param  s: The string to output.
 * @param  n: The number of characters to output.
 * @param  fd: The file descriptor  on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putnstr_fd(char *s, int n, int fd);

/**
 * @brief  Outputs the string ’s’ to the specified file descriptor
 *  followed by a newline.
 * @param  s: The string to output.
 * @param  fd: The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putendl_fd(char *s, int fd);

/**
 * @brief  Outputs the integer ’n’ to the specified file descriptor.
 * @param  n: The integer to output.
 * @param  fd:   The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */

int					ft_putlnbr_fd(long n, int fd);
/**
 * @brief  Outputs the integer ’n’ to the specified file descriptor.
 * @param  n:  The integer to output.
 * @param  fd:  The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putnbr_fd(int n, int fd);

/**
 * @brief  Outputs the unsigned long ’nbr’ to the specified file descriptor
 * with a specified base.
 * @param  nbr: The integer to output.
 * @param  base: The base of number to output.
 * @param  fd: The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putulnbr_base_fd(unsigned long nbr, char *base, int fd);

/**
 * @brief  Outputs the long ’nbr’ to the specified file descriptor
 * with a specified base.
 * @param  nbr: The integer to output.
 * @param  base: The base of number to output.
 * @param  fd: The file descriptor on which to write.
 * @retval The number of written characters or -1 if an error.
 */
int					ft_putlnbr_base_fd(long nbr, char *base, int fd);

/**
 * @brief  Return the minimal number of given two.
 * @param  a: The first number.
 * @param  b: The second number.
 * @retval Minimal number.
 */
int					ft_min(int a, int b);

/**
 * @brief  Return the maximal number of given two.
 * @param  a: The first number.
 * @param  b: The second number.
 * @retval Maximal number.
 */
int					ft_max(int a, int b);

/**
 * @brief  Allocates memory (using malloc(3)) and returns a new node.
 *  The ’content’ member variable is initialized with
 * 	the given parameter ’content’. The variable ’next’ is initialized to NULL.
 * @param  content: The content to store in the new node.
 * @retval A pointer to the new node.
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief  Adds the node ’new’ at the beginning of the list.
 * @param  lst: The address of a pointer to the first node of a list.
 * @param  new: The address of a pointer to the node to be added.
 * @retval None.
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief  Counts the number of nodes in the list.
 * @param  lst: The beginning of the list.
 * @retval The length of the list.
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief  Returns the last node of the list.
 * @note
 * @param  *lst:
 * @retval Last node of the list.
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief  Adds the node ’new’ at the end of the list.
 * @param  lst: The address of a pointer to the first node of a list.
 * @param  new: The address of a pointer to the node to be added.
 * @retval None.
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief  Takes a node as parameter and frees its content using
 *  the function ’del’. Free the node itself but does NOT free the
 *  next node.
 * @param  lst: The node to free.
 * @param  del: The address of the function used to delete the content.
 * @retval None.
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief  Deletes and frees the given node and all its successors,
 *  using the function ’del’ and free(3). Finally, set the pointer
 *  to the list to NULL.
 * @param  lst: The address of a pointer to a node.
 * @param  del: The address of the function used to delete
 *  the content of the node.
 * @retval None
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates through the list ’lst’ and applies
 *  the function ’f’ to the content of each node.
 * @param  lst: The address of a pointer to a node.
 * @param  f: The address of the function to apply to each node’s content.
 * @retval None.
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief  Iterates through the list ’lst’, applies the function ’f’ to each
 *  node’s content, and creates a new list resulting of the successive
 *  applications of the function ’f’. The ’del’ function is used to delete
 *  the content of a node if needed.
 * @param  lst: The address of a pointer to a node.
 * @param  f: The address of the function applied to each node’s content.
 * @param  del: The address of the function used to delete
 *  a node’s content if needed.
 * @retval The new list.
 * 			NULL if the allocation fails.
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief  Write a function that returns a line read from a file descriptor.
 * @param  fd: The file descriptor to read from.
 * @retval Read line: correct behavior
 * * NULL: there is nothing else to read, or an error occurred.
 */
char				*get_next_line(int fd);
#endif