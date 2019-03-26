# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/03/26 12:29:28 by llopez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 1

TARGETS		:= corewar asm
LIBS		:= libft

corewar_LIB	:= ft

asm_LIB		:= ft

corewar_SRC	:=	op.c \
				corewar/main.c \
				corewar/init.c \
				corewar/utils.c \
				corewar/execution.c \
				corewar/op.c

asm_SRC		:=	op.c \
				asm/interpret.c \
				asm/main.c \
				asm/splitwhitespaces.c \
				asm/lexer.c \
				asm/utils.c

include generic_c.mk
