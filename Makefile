# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/04/12 12:00:43 by llopez           ###   ########.fr        #
=======
#    Updated: 2019/04/12 12:51:12 by jdouniol         ###   ########.fr        #
>>>>>>> 675241621fd75fd9921441ce8a62d3cbbb0034de
#                                                                              #
# **************************************************************************** #

CC			:= gcc

DEBUG 		:= 1

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
				asm/asm_03_interpret.c \
				asm/asm_00_main.c \
				asm/asm_01_check_args.c \
				asm/asm_02a_check_file.c \
				asm/asm_02b_check_params_and_labels.c \
				asm/asm_02c_check_name_and_header.c \
				asm/asm_02d_check_file_jumps.c \
				asm/asm_02e_check_file_utils.c \
				asm/asm_09a_utils.c \
				asm/asm_09b_label_pos.c \
				asm/asm_04_translate.c

include generic_c.mk
