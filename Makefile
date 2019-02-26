# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/02/26 17:27:58 by pcarles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 1

TARGETS		:= corewar
LIBS		:= libft

asm_LIB		:= ft
corewar_LIB	:= ft

asm_SRC		:=	asm/main.c \
				asm/parser.c \
				asm/label.c \
				asm/utils.c \
				asm/op.c \
				asm/lexer.c

corewar_SRC	:=	corewar/main.c \
				corewar/init.c \
				corewar/utils.c

include generic_c.mk