# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/04/11 21:34:08 by llopez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 0

TARGETS		:= corewar asm
LIBS		:= libft

corewar_LIB	:= ft

asm_LIB		:= ft

corewar_SRC	:=	op.c \
				utils.c \
				corewar/cw_00_main.c \
				corewar/cw_01_init.c \
				corewar/cw_02_load.c \
				corewar/cw_03_cycle.c \
				corewar/cw_04_execution.c \
				corewar/read_args.c \
				corewar/cw_05a_op.c \
				corewar/cw_05b_op1.c \
				corewar/cw_05c_op2.c \
				corewar/cw_05d_op3.c \
				corewar/cw_09a_options.c \
				corewar/cw_09b_utils.c \
				corewar/cw_09c_memory.c

asm_SRC		:=	op.c \
				utils.c \
				asm/interpret.c \
				asm/main.c \
				asm/splitwhitespaces.c \
				asm/utils.c \
				asm/label_pos.c \
				asm/check_file.c \
				asm/translate.c \
				asm/check_file_jumps.c \
				asm/check_file_utils.c

include generic_c.mk
