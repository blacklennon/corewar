/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:30:17 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/27 00:29:38 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	La fonction op_sub realise une soustraction entre deux valeurs
**	et charge le resultat dans un registre
**	ces valeurs sont forcement dans des registres
*/

void		op_sub(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	result = process->registers[args->value[0].u_reg]
		- process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose >= 2)
	{
		ft_printf("Player N %d is doing SUB\n", process->champion->id);
		if (vm->verbose == 3)
		{
			ft_printf("Value is %d, (%d - %d), stored in reg %d\n", result,\
				process->registers[args->value[0].u_reg],\
				process->registers[args->value[1].u_reg], args->value[2].u_reg);
		}
	}
}

/*
**	La fonction op_and realise un et bianire entre deux valeurs
**	et charge le resultat dans un registre
**	ces valeurs peuvent etre donnees par des ind, des dir ou des registres
*/

void		op_and(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	get_value_of_arg(process, &args->value[0], &args->type[0], AND);
	get_value_of_arg(process, &args->value[1], &args->type[1], AND);
	result = args->value[0].u_dir32 & args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose >= 2)
	{
		ft_printf("Player N %d is doing AND\n", process->champion->id);
		if (vm->verbose == 3)
		{
			ft_printf("Value is %d, (%d & %d), stored in reg %d\n", result,\
				process->registers[args->value[0].u_reg],\
				process->registers[args->value[1].u_reg], args->value[2].u_reg);
		}
	}
}

/*
**	La fonction op_or realise un ou inclusif entre deux valeurs
**	et charge le resultat dans un registre
**	ces valeurs peuvent etre donnees par des ind, des dir ou des registres
*/

void		op_or(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	get_value_of_arg(process, &args->value[0], &args->type[0], OR);
	get_value_of_arg(process, &args->value[1], &args->type[1], OR);
	result = args->value[0].u_dir32 | args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose >= 2)
	{
		ft_printf("Player N %d is doing OR\n", process->champion->id);
		if (vm->verbose == 3)
		{
			ft_printf("Value is %d, (%d | %d), stored in reg %d\n", result,\
				process->registers[args->value[0].u_reg],\
				process->registers[args->value[1].u_reg], args->value[2].u_reg);
		}
	}
}

/*
**	La fonction op_xor realise un ou exclusif entre deux valeurs
**	et charge le resultat dans un registre
**	ces valeurs peuvent etre donnees par des ind, des dir ou des registres
*/

void		op_xor(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	get_value_of_arg(process, &args->value[0], &args->type[0], XOR);
	get_value_of_arg(process, &args->value[1], &args->type[1], XOR);
	result = args->value[0].u_dir32 ^ args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose >= 2)
	{
		ft_printf("Player N %d is doing XOR\n", process->champion->id);
		if (vm->verbose == 3)
		{
			ft_printf("Value is %d, (%d ^ %d), stored in reg %d\n", result,\
				process->registers[args->value[0].u_reg],\
				process->registers[args->value[1].u_reg], args->value[2].u_reg);
		}
	}
}

/*
**	La fonction op_zjmp realise un jump a la case memoire
**	passee en prametre, si le carry est a 1
*/

void		op_zjmp(t_process *process, t_args *args)
{
	t_vm	*vm;

	vm = get_vm(NULL);
	if (process->carry == 1)
		process->program_counter += args->value[0].u_dir16;
	if (vm->verbose >= 2)
	{
		ft_printf("Player N %d is doing ZJMP\n", process->champion->id);
		if (vm->verbose == 3)
		{
			ft_printf("PC is advancing of %d bytes,then new pc is %d\n",\
				args->value[0].u_dir16, process->program_counter);
		}
	}
}
