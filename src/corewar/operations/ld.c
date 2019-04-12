/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:23:21 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 13:31:03 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	La fonction op_ld va charger la valeur trouvee dans la vm via un dir32
**	ou dans un indirect de 16
**	cette valeur est chargee dans le registre de destination
*/

void		op_ld(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	get_value_of_arg(process, &args->value[0], &args->type[0], LD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose == 3)
		ft_printf("Value of LD : %d loaded in reg %d\n",\
			result, args->value[1].u_reg);
}

/*
**	La fonction op_lld fonctionne comme un direct load (LD), mais sans
**	restriction d adressage, a savoir, on charge un valeur en 16 (ind)
**	ou 32 bits (dir), et on la charge dans le registre passe en 2eme
**	parametre
*/

void		op_lld(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	get_value_of_arg(process, &args->value[0], &args->type[0], LLD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose == 3)
		ft_printf("Value of LLD : %d loaded in reg %d\n",\
			result, args->value[1].u_reg);
}

/*
**	LDI Reste a commenter, et a appliquer le verbose
*/

void		op_ldi(t_process *process, t_args *args)
{
	int32_t	value;
	int32_t	address;

	address = 0;
	get_value_of_arg(process, &args->value[0], &args->type[0], LDI);
	get_value_of_arg(process, &args->value[1], &args->type[1], LDI);
	if (args->type[0] == e_result && args->type[1] != e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir16;
	else if (args->type[0] == e_result && args->type[1] == e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir32;
	else if (args->type[0] != e_result && args->type[1] != e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir16;
	else if (args->type[0] != e_result && args->type[1] == e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir32;
	else
		crash(process, "This should never been reached op2.c:38");
	value = read4_memory(get_vm(NULL), \
	process->program_counter + (address % IDX_MOD));
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
}

/*
**	LLDI Reste a commenter, et a appliquer le verbose
*/

void		op_lldi(t_process *process, t_args *args)
{
	int32_t	value;
	int32_t	address;

	address = 0;
	get_value_of_arg(process, &args->value[0], &args->type[0], LLDI);
	get_value_of_arg(process, &args->value[1], &args->type[1], LLDI);
	if (args->type[0] == e_result && args->type[1] != e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir16;
	else if (args->type[0] == e_result && args->type[1] == e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir32;
	else if (args->type[0] != e_result && args->type[1] != e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir16;
	else if (args->type[0] != e_result && args->type[1] == e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir32;
	else
		crash(process, "This should never been reached op3.c:37");
	value = read4_memory(get_vm(NULL), process->program_counter + address);
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
}
