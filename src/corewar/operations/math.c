/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:24:59 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 13:25:27 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	La fonction op_add realise une addition entre deux valeurs
**	et charge le resultat dans un registre
**	ces valeurs sont forcement dans des registres
*/

void		op_add(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	result = process->registers[args->value[0].u_reg]\
		+ process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose == 3)
	{
		ft_printf("Value is %d, (%d + %d), stored in reg %d\n", result,\
			process->registers[args->value[0].u_reg],\
			process->registers[args->value[1].u_reg], args->value[2].u_reg);
	}
}

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
	if (vm->verbose == 3)
	{
		ft_printf("Value is %d, (%d - %d), stored in reg %d\n", result,\
			process->registers[args->value[0].u_reg],\
			process->registers[args->value[1].u_reg], args->value[2].u_reg);
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
	if (vm->verbose == 3)
	{
		ft_printf("Value is %d, (%d & %d), stored in reg %d\n", result,\
			args->value[0].u_dir32,\
			args->value[1].u_dir32, args->value[2].u_reg);
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
	if (vm->verbose == 3)
	{
		ft_printf("Value is %d, (%d | %d), stored in reg %d\n", result,\
			args->value[0].u_dir32,\
			args->value[1].u_dir32, args->value[2].u_reg);
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
	if (vm->verbose == 3)
	{
		ft_printf("Value is %d, (%d ^ %d), stored in reg %d\n", result,\
			args->value[0].u_dir32,\
			args->value[1].u_dir32, args->value[2].u_reg);
	}
}
