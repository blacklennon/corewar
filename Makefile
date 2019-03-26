# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/03/26 22:29:32 by jdouniol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 1

TARGETS		:= corewar
LIBS		:= libft

corewar_LIB	:= ft

corewar_SRC	:=	op.c \
				utils.c \
				corewar/main.c \
				corewar/init.c \
				corewar/utils.c \
				corewar/execution.c \
				corewar/op.c \
				corewar/op1.c \
				corewar/op2.c \
				corewar/op3.c \
				corewar/memory.c \
				corewar/cycle.c \
				corewar/options.c

include generic_c.mk