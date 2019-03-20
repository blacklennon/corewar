/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/16 20:33:00 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"

/* OBSOLETE

void		ft_set_type_aux(uint8_t *ft, t_instruct *instruct) // l'appeler avec t_process->instruct?
{
	if (*ft == 0x0b)
		instruct->type = STI;
	else if (*ft == 0x0c)
		instruct->type = FORK;
	else if (*ft == 0x0d)
		instruct->type = LLD;
	else if (*ft == 0x0e)
		instruct->type = LLDI;
	else if (*ft == 0x0f)
		instruct->type = LFORK;
	else if (*ft == 0x10)
		instruct->type = AFF;
}

void 		ft_set_type(uint8_t *ft, t_instruct *instruct)
{
	if (*ft == 0x01)
		instruct->type = LIVE;
	else if (*ft == 0x02)
		instruct->type = LD;
	else if (*ft == 0x03)
		instruct->type = ST;
	else if (*ft == 0x04)
		instruct->type = ADD;
	else if (*ft == 0x05)
		instruct->type = SUB;
	else if (*ft == 0x06)
		instruct->type = AND;
	else if (*ft == 0x07)
		instruct->type = OR;
	else if (*ft == 0x08)
		instruct->type = XOR;
	else if (*ft == 0x09)
		instruct->type = ZJMP;
	else if (*ft == 0x0a)
		instruct->type = LDI;
	else
		ft_set_type_aux(ft, instruct);
}

typedef struct 			s_instruct
{
	t_type				type;
//	int					tab_utils[9];
	uint8_t				ocp;
	uint32_t			nb_champ;
	uint8_t				reg_1_0;
	uint8_t				reg_2_1;
	uint8_t				reg_3_2;
	uint16_t			ind_1_3;
	uint16_t			ind_2_4;
	uint16_t			dir_16_1_5;
	uint16_t			dir_16_2_6;
	uint32_t			dir_32_1_7;
	uint32_t			dir_32_2_8;
	struct s_instruct	*prev; // inutile
	struct s_instruct	*next; // inutile
	int32_t				value_reg1;
	int32_t				value_reg2;
	int32_t				value_reg3;
}						t_instruct;


	int32_t				registers[REG_NUMBER];

void	ft_set_value_of_registre(t_vm *vm, t_process *process)
{
	uint32_t	all;
	uint32_t	all_tmp;
	process->registers[process->instruct->reg_1_0] = 2;
	process->registers[process->instruct->reg_2_1] = 3; 
	process->registers[process->instruct->reg_3_2] = 0;


	ft_memcpy(&all, vm->memory[process->program_counter + 2 % MEM_SIZE]) // jouer d abord avec les masques
//	all_tmp = all;
	all_tmp = (all & 0xFF000000);
	process->instruct->reg_1_0 = all_tmp >> 24;
	all_tmp = (all & 0x00FF0000);
	process->instruct->reg_2_1 = all_tmp >> 16;
	all_tmp = (all & 0x0000FF00);
	process->instruct->reg_3_2 = all_tmp >> 8;
	process->registers[process->instruct->reg_3_2] = process->registers[process->instruct->reg_1_0] + process->registers[process->instruct->reg_2_1];
	ft_printf("reg1 = %x, reg 2 = %x, reg3 = %x\n", process->registers[process->instruct->reg_1_0], process->registers[process->instruct->reg_2_1],  process->registers[process->instruct->reg_3_2]);
	process->carry = (process->registers[process->instruct->reg_3_2] == 0) ? 1 : 0;

}

void	check_ocp_add(t_vm *vm, t_process *process)
{
	uint8_t	ocp;

	ocp = vm->memory[++process->program_counter % MEM_SIZE];
	if (ocp != 0x54)
		return;//ft_crash();
	else
	{
		ft_get_value_of_registre(vm, process);
	//	ft_do_add_operation(vm, process); pas besoin a cette heure
	}
}

void	ft_help_add(t_vm *vm, t_process *process)
{
	check_ocp_add(vm, process);
	ft_set_value_of_registre(vm, process);
	//ft_do_add(vm, process);
}


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

*/