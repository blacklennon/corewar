# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 14:47:37 by pcarles           #+#    #+#              #
#    Updated: 2019/04/12 15:06:44 by jdouniol         ###   ########.fr        #
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
				asm/asm_00_main.c \
				asm/asm_01_check_args.c \
				asm/asm_01b_print_and_fill_header.c \
				asm/asm_01c_clean_data.c \
				asm/asm_02a_check_file.c \
				asm/asm_02b_check_params_and_labels.c \
				asm/asm_02c_check_name_and_header.c \
				asm/asm_02d_check_file_jumps.c \
				asm/asm_02e_check_file_utils.c \
				asm/asm_03_interpret.c \
				asm/asm_04_translate.c \
				asm/asm_05_translate.c \
				asm/asm_09a_label_pos.c \
				asm/asm_09b_utils.c \
				asm/asm_09c_utils.c

include generic_c.mk
