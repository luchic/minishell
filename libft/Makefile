# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 14:55:17 by mezhang           #+#    #+#              #
#    Updated: 2025/08/22 14:13:26 by mezhang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### I - Define comman rules ###
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

### II - Define variables ###
SRCS = 	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_striteri.c \
		ft_printf_hex.c \
		ft_printf_nbr.c \
		ft_printf_ptr.c \
		ft_printf_str.c \
		ft_printf_uint.c \
		ft_printf.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)


### III - Define executive rules ###
all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
