# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/03/20 19:52:01 by jdouniol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 1

TARGETS		:= corewar
LIBS		:= libft

corewar_LIB	:= ft

corewar_SRC	:=	corewar/main.c \
				corewar/init.c \
				corewar/utils.c \
				corewar/execution.c \
				corewar/op.c \
				corewar/memory.c \
				corewar/cycle.c

include generic_c.mk