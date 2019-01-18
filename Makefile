# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/01/18 18:42:43 by pcarles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= asm

CC			?= gcc
C_FLAGS		?= -Wall -Wextra -Werror -fsanitize=address -g
LD_FLAGS	?= -fsanitize=address -g

SRCDIR		= src/
HDRDIR		= includes/
LIBDIR		= libft/
BINDIR		= bin/

C_FILES		= main.c \
			parser.c \
			label.c \
			utils.c \
			op.c \
			lexer.c

LIBFT		= $(LIBDIR)libft.a

SRC			= $(addprefix $(SRCDIR), $(C_FILES))
OBJ			= $(patsubst %.c, %.o, $(addprefix $(BINDIR), $(notdir $(SRC))))

VPATH		= $(shell find $(SRCDIR) -type d)

export CC C_FLAGS LD_FLAGS

.PHONY: all clean fclean re norm

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -o $@ -I$(HDRDIR) -L$(LIBDIR) -lft $(OBJ) $(LD_FLAGS)
	@echo "\033[32;1mCreated $@\033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBDIR)

$(BINDIR)%.o: %.c
	@mkdir -p $(BINDIR)
	@$(CC) -o $@ -I$(HDRDIR) -c $< $(C_FLAGS)
	@echo "\033[33mCompiling $@\033[0m"

clean:
	@$(MAKE) -C $(LIBDIR) $@
	@rm -rf $(BINDIR)
	@echo "\033[31;1mRemoved $(BINDIR)\033[0m"

fclean: clean
	@$(MAKE) -C $(LIBDIR) $@
	@rm -f $(NAME)
	@echo "\033[31;1mRemoved $(NAME)\033[0m"

re: fclean all

norm:
	@norminette $(SRCDIR) $(HDRDIR)