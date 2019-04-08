# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/04/08 13:59:41 by llopez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 0

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
				asm/utils.c \
				asm/label_pos.c \
				asm/translate.c

include generic_c.mk
