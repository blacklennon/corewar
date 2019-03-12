/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/12 22:50:32 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

#include "corewar.h"

int32_t			read4_memory(t_vm *vm, size_t index)
{
	int32_t		*tmp;
	uint8_t		tab[4];
	size_t		i;

	index %= MEM_SIZE;
	if (MEM_SIZE - index > 4)
		tmp = (int32_t*)&vm->memory[index];
	else
	{
		tmp = (int32_t*)tab;
		i = 0;
		ft_bzero(tab, sizeof(tab));
		while (i < 4)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
	}
	return (swap_int32(*tmp));
}

int16_t			read2_memory(t_vm *vm, size_t index)
{
	int16_t		*tmp;
	uint8_t		tab[2];
	size_t		i;

	index %= MEM_SIZE;
	if (MEM_SIZE - index > 2)
		tmp = (int16_t*)&vm->memory[index];
	else
	{
		tmp = (int16_t*)tab;
		i = 0;
		ft_bzero(tab, sizeof(tab));
		while (i < 2)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
	}
	return (swap_int16(*tmp));
}

void		write4_memory(t_vm *vm, int32_t value, size_t index)
{
	int32_t		*tmp;
	uint8_t		tab[4];
	size_t		i;

	tmp = (int32_t*)tab;
	*tmp = swap_int32(value);
	i = 0;
	while (i < 4)
	{
		index %= MEM_SIZE;
		vm->memory[index] = tab[i];
		index++;
		i++;
	}
}

void		op_live(t_process *process, t_args *args, t_vm *vm)
{
	int32_t	arg;

	arg = args->value[0].u_dir32;
	if (arg > 0 && arg <= (int)vm->nb_champs)
		vm->process[arg - 1].live_counter++;
	printf("player %d is alive\n", arg);
	process->program_counter += 4;
}

void		op_zjmp(t_process *process, t_args *args, t_vm *vm)
{
	(void)vm;
	if (process->carry == 1)
		process->program_counter += args->value[0].u_dir16;
	else
		process->program_counter += 3;
}

void		op_aff(t_process *process, t_args *args, t_vm *vm)
{
	uint8_t	ocp;

	(void)args;
	ocp = vm->memory[++process->program_counter % MEM_SIZE];
	if (ocp != 0x40)
		//crash ?
	ocp = vm->memory[++process->program_counter % MEM_SIZE];
	if (ocp > 0 && ocp <= REG_NUMBER)
		printf("process %s is saying `%c'\n", process->name, process->registers[ocp - 1] % 256);
	else
		//crash ?
	process->program_counter++;
}

// int32_t ft_addition(int32_t arg1, int32_t arg2)
// {
// 	return (arg1 + arg2);
// }

// int32_t ft_substraction(int32_t arg1, int32_t arg2)
// {
// 	return (arg1 - arg2);
// }

// int32_t ft_substraction(int32_t arg1, int32_t arg2)
// {
// 	return (arg1 - arg2);
// }

// typedef union			u_int_types_enum
// {
// 	int_8, int_16, int_32
// }						t_int_types_enum;

// typedef	struct 			s_ocp
// {
// 	t_int_types_enum	first_param_type;
// 	t_int_types			first_param;
// 	t_int_types_enum	second_param_type;
// 	t_int_types			second_param;
// 	t_int_types_enum	third_param_type;
// 	t_int_types 		third_param;
// }						t_ocp;


// void	decode_param()
// {

// }

// void	read_ocp(t_vm vm, size_t index, t_ocp *ocp, t_op op)
// {
// 	// verifer selon VM ET INDEX que les params sont equivalent a ce que veut le t_op
// 	// recuperer chaque param et leur type selon ce que t_op veut (int_16 ou int_32 p.e)
// 	// remplir t_ocp avec ses info
// 	// VERIF_PARAMS
// 	// DECODE_PARAMS
// 	op->params[0];
// 	if (op->params[0] && 0x1)

// }

// void	op_xor(t_vm *vm, t_process *process)
// {
// 	t_ocp ocp;
// 	int32_t  x;

// 	//read_ocp(vm, process->program_counter, &ocp);
// 	// ICi tu recuperes les bonnes info de la globale
 
//  	reac_ocp(vm, process->program_counter, &ocp, op_tab[XOR]);
//  	// REG IND DIR
//  	if (REG)
//  		x = ocp->first_param.reg;
//  	// REG IND DIR

//  	// REG
//  	ocp->last_params.reg;


//  	//{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}
// 	// op_tab[XOR - 1] 
// }

// void	ft_set_value_of_registrers(t_vm *vm, t_process *process, int32_t(*f)(int32_t, int32_t)) // utilitaire pour tous les R R R
// {
// 	int32_t	all;
// 	int32_t	all_tmp;

// 	all = read4_memory(vm, ++process->program_counter);
// //	printf("all = %x\n", all);
// 	all_tmp = (all & 0xFF000000);
// 	process->instruct.reg_1_0 = all_tmp >> 24;
// 	all_tmp = (all & 0x00FF0000);
// 	process->instruct.reg_2_1 = all_tmp >> 16;
// 	all_tmp = (all & 0x0000FF00);
// 	process->instruct.reg_3_2 = all_tmp >> 8;
// //	process->registers[process->instruct.reg_1_0] = 1;
// //	process->registers[process->instruct.reg_2_1] = 3; 
// //	process->registers[process->instruct.reg_3_2] = 0;
// 	process->registers[process->instruct.reg_3_2] = f(process->registers[process->instruct.reg_1_0], process->registers[process->instruct.reg_2_1]);

// //	process->registers[process->instruct.reg_3_2] = process->registers[process->instruct.reg_1_0] + process->registers[process->instruct.reg_2_1];
// 	printf("ici les registres appeles sont  reg1 = %x, reg 2 = %x, reg3 = %x\n", process->instruct.reg_1_0, process->instruct.reg_2_1,  process->instruct.reg_3_2);
// 	printf("apres reg1 = %x, reg 2 = %x, reg3 = %x\n", process->registers[process->instruct.reg_1_0], process->registers[process->instruct.reg_2_1],  process->registers[process->instruct.reg_3_2]);
// 	process->carry = (process->registers[process->instruct.reg_3_2] == 0) ? 1 : 0;
// 	process->program_counter += 4;
// 	process->next_op = vm->cycle + 10;
// }

// void	op_add(t_process *process, t_vm *vm)
// {
// 	uint8_t	ocp;
// 	t_ocp	ocp_struct;

// 	read_ocp(vm, process->program_counter, &ocp_struct, op_tab[ADD]);
// 	ocp_struct.first_param.reg + ocp_struct.second_param.reg + ocp_struct.third_param.req;


// 	ocp = vm->memory[++process->program_counter % MEM_SIZE];
// 	if (ocp != 0x54)
// 		return;//ft_crash();
// 	else
// 		ft_set_value_of_registrers(vm, process, &ft_addition);
// }

// void	op_sub(t_process *process, t_vm *vm)
// {
// 	uint8_t	ocp;

// 	ocp = vm->memory[++process->program_counter % MEM_SIZE];
// 	if (ocp != 0x54)
// 		return;//ft_crash();
// 	else
// 		ft_set_value_of_registrers(vm, process, &ft_substraction);
// }


// // void		ld(t_process *process, t_vm *vm)
// // {
// // 	process->next_op = vm->cycle + 5;
// // }