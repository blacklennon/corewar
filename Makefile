# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/04/09 18:49:07 by pcarles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 1

TARGETS		:= corewar
LIBS		:= libft

corewar_LIB	:= ft

corewar_SRC	:=	op.c \
				utils.c \
				corewar/cw_00_main.c \
				corewar/cw_01_init.c \
				corewar/cw_02_load.c \
				corewar/cw_03_cycle.c \
				corewar/cw_04_execution.c \
				corewar/cw_04a_read_args.c \
				corewar/cw_05a_op.c \
				corewar/cw_05b_op1.c \
				corewar/cw_05c_op2.c \
				corewar/cw_05d_op3.c \
				corewar/cw_09a_options.c \
				corewar/cw_09b_options.c \
				corewar/cw_09b_utils.c \
				corewar/cw_09c_memory.c

include generic_c.mk