# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 15:41:57 by pcarles           #+#    #+#              #
#    Updated: 2019/02/26 17:30:45 by pcarles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET_PATH	?= .

CC			?= gcc
C_FLAGS		?= -Wall -Wextra -Werror
LD_FLAGS	?=

NAME		= $(addprefix $(TARGET_PATH)/,libft.a)

BINDIR		= bin
SRCDIR		= src
INCLDIR		= includes

H_FILES		= libft.h \
			get_next_line.h

C_FILES		= ft_putchar.c \
			ft_strlen.c \
			ft_putstr.c \
			ft_putnstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_atoi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memalloc.c \
			ft_memmove.c \
			ft_memdel.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strlcat.c \
			ft_itoa.c \
			ft_strsplit.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_pow.c \
			ft_islower.c \
			ft_isupper.c \
			ft_isspace.c \
			ft_isxdigit.c \
			get_next_line.c \
			ft_printf/ft_printf.c \
			ft_printf/init_handlers.c \
			ft_printf/parser.c \
			ft_printf/utils_2.c \
			ft_printf/utils.c \
			ft_printf/converter.c \
			ft_printf/handlers/char.c \
			ft_printf/handlers/hexa.c \
			ft_printf/handlers/int.c \
			ft_printf/handlers/octal.c \
			ft_printf/handlers/pointer.c \
			ft_printf/handlers/unsigned.c \
			ft_printf/handlers/wchar.c \

SRC			= $(addprefix $(SRCDIR)/, $(C_FILES))
HDRS		= $(addprefix $(INCLDIR)/, $(H_FILES))
OBJ			= $(patsubst %.c, %.o, $(addprefix $(BINDIR)/, $(notdir $(SRC))))

VPATH		= $(shell find src -type d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(dir $(NAME))
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[32;1mCreated $@\033[0m"

$(BINDIR)/%.o: %.c $(HDRS)
	@mkdir -p $(BINDIR)
	@$(CC) -o $@ -c $< -I $(INCLDIR) $(FLAGS)
	@echo "\033[33mCompiling $@\033[0m"

clean:
	@rm -rf $(BINDIR)
	@echo "\033[31;1mRemoved $(BINDIR)\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31;1mRemoved $(NAME)\033[0m"

re: fclean all
