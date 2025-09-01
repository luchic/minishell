# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:35:53 by nluchini          #+#    #+#              #
#    Updated: 2025/08/30 16:40:18 by nluchini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Mandatory part of the project

# Src
SRC = src
ROOT = core

LIBFT_CORE_FILES =	ft_atoi.c \
					ft_atof.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_realloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_islower.c \
					ft_isupper.c \
					ft_itoa.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_min.c \
					ft_max.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_putnstr_fd.c \
					ft_putlnbr_fd.c \
					ft_putlnbr_base_fd.c\
					ft_putulnbr_base_fd.c\
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strcmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_striteri.c \
					ft_lstadd_back_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstmap_bonus.c \
					ft_lstnew_bonus.c \
					ft_lstsize_bonus.c

# Core library
CORE_FIlES = $(addprefix $(SRC)/$(ROOT)/, $(LIBFT_CORE_FILES))
CORE_OBJ_FIlES = $(CORE_FIlES:.c=.o)

# Ft_printf
PATH_PRINTF = ft_printf

PARSER = 		$(SRC)/$(PATH_PRINTF)/parser
PRINTER = 		$(SRC)/$(PATH_PRINTF)/printer
TOOLS = 		$(SRC)/$(PATH_PRINTF)/tools
CORE = 			$(SRC)/$(PATH_PRINTF)/core

# Src files

## Core
PRINTF_CORE = 	$(CORE)/ft_vfprintf_fd.c \
				$(CORE)/ft_printf.c \
				$(CORE)/ft_printf_fd.c
PROBJ_CORE = 	$(PRINTF_CORE:.c=.o)

## Parser
SRC_PARSER = 	$(PARSER)/ft_parser.c
OBJ_PARSER = 	$(SRC_PARSER:.c=.o)

## Printer
SRC_PRINTER = 	$(PRINTER)/ft_printer.c \
				$(PRINTER)/ft_print_integer.c \
				$(PRINTER)/ft_print_pointer.c \
				$(PRINTER)/ft_print_string.c \
				$(PRINTER)/ft_print_uinteger.c
OBJ_PRINTER = 	$(SRC_PRINTER:.c=.o)

## Tools
SRC_TOOLS = 	$(TOOLS)/ft_number_utils.c \
				$(TOOLS)/ft_format_utils.c \
				$(TOOLS)/ft_flag_parser.c \
				$(TOOLS)/ft_format_validator.c \
				$(TOOLS)/ft_platform_utils.c \
				$(TOOLS)/ft_ptr_format.c
OBJ_TOOLS = 	$(SRC_TOOLS:.c=.o)

## All Src files
SRC_PRINTF += $(PRINTF_CORE)
SRC_PRINTF += $(SRC_PARSER)
SRC_PRINTF += $(SRC_PRINTER)
SRC_PRINTF += $(SRC_TOOLS)

## All Object files
OBJ_PRINTF += $(PROBJ_CORE)
OBJ_PRINTF += $(OBJ_PARSER)
OBJ_PRINTF += $(OBJ_PRINTER)
OBJ_PRINTF += $(OBJ_TOOLS)

## Get Next Line
GNL = $(SRC)/get_next_line

GNL_SRC =	$(GNL)/get_next_line.c \
			$(GNL)/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

#Include
HEADER = includes

# Compiler and flags
CFLAGS = -Wall -Wextra -Werror -I$(HEADER) 
CC = cc

all : $(NAME)

$(NAME) : $(CORE_OBJ_FIlES) $(OBJ_PRINTF) $(GNL_OBJ)
	ar rcs $(NAME) $(CORE_OBJ_FIlES) $(OBJ_PRINTF) $(GNL_OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

re : fclean all

fclean : clean
	rm -f $(NAME) 

clean : 
	rm -f $(CORE_OBJ_FIlES) $(OBJ_PRINTF) $(GNL_OBJ)

.PHONY: all clean fclean re 