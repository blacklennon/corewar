/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/28 17:57:33 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"

typedef enum 	e_type
{
	LIVE, LD, ST, ADD, SUB, AND, OR XOR, ZJMP, LDI, STI, FORK, LLD, LLDI,\
	LFORK, AAF
}				t_type;


/*
**	LIVE CONTIENT SIMPLEMENT UN T_DIR code sur 2 ou 4 octets
**	LD CONTIENT 
**
**
**
**
**
**
**
**
*/

typedef struct 			s_instruct
{
	t_type				type;
	int					tab_utils[9];
	uint8_t				reg_1_0;
	uint8_t				reg_2_1;
	uint8_t				reg_3_2;
	uint16_t			ind_1_3;
	uint16_t			ind_2_4;
	uint16_t			dir_16_1_5;
	uint16_t			dir_16_2_6;
	uint32_t			dir_32_1_7;
	uint32_t			dir_32_2_8;
	struct t_instruct	*prev;
	struct t_instruct	*next;
}						t_instruct;

int 	ft_init_struct_instruct(t_vm *vm, t_instruct *instruct)
{

}


int		ft_print_binary_of_all_instruct_and_args(t_vm *vm, int index, int size)
{

}

int		ft_print_hexa_of_all_instruct_and_args(t_vm *vm, int index, int size)
{

}

int		ft_print_struct_instruct(t_instruct *current)

int 	ft_parse_instructions(t_vm *vm)
{

}