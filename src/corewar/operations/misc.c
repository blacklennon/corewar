/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:26:07 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 13:31:45 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "corewar.h"

void		get_value_of_arg(t_process *process, t_int_types *value, \
			t_int_types_enum *type, int opcode)
{
	if (*type == e_reg)
		(*value).u_dir32 = process->registers[(*value).u_reg];
	else if (*type == e_ind && (opcode == LLD || opcode == LLDI))
		(*value).u_dir32 = read4_memory(get_vm(NULL), \
				process->program_counter + (*value).u_ind);
	else if (*type == e_ind)
		(*value).u_dir32 = read4_memory(get_vm(NULL), \
				process->program_counter + ((*value).u_ind) % IDX_MOD);
	if (*type == e_reg || *type == e_ind)
		(*type) = e_result;
}

/*
**	La fonction op_live va dire qu un joueur est en vie
**	on prend les 4 octets qui suivent l opcode live
**	et on declare ce champion comme etant en vie
**	Si le numero de joueur n existe pas, le live est compte,
**	mais n est utile pour aucun joueur
*/

void		op_live(t_process *process, t_args *args)
{
	int32_t	arg;
	t_vm	*vm;

	vm = get_vm(NULL);
	arg = args->value[0].u_dir32;
	process->live_counter++;
	if (arg > 0 && arg <= MAX_PLAYERS \
		&& vm->champions[arg - 1].file_path != NULL)
	{
		vm->last_alive = &vm->champions[arg - 1];
		if (vm->verbose >= 1)
			ft_printf("\e[%dmPlayer %d (%s) is alive\e[0m\n", \
		31 + arg, arg, vm->champions[arg - 1].name);
	}
	else
	{
		if (vm->verbose >= 1)
			ft_printf("unknown player %d is alive\n", arg);
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
	{
		process->program_counter += args->value[0].u_dir16;
		if (vm->verbose == 3)
		{
			ft_printf("PC is advancing of %d bytes,then new pc is %d\n",\
			args->value[0].u_dir16, process->program_counter);
		}
	}
}

/*
**	La fonction op_aff permet d'afficher la valeur en char % 256 du registre
**	passe en parametre, peut permettre de faire des phrases completes avec
**	un peu d'acharnement
*/

void		op_aff(t_process *process, t_args *args)
{
	char	value;

	value = (char)(process->registers[args->value[0].u_reg] % 256);
	ft_printf("Process %s is saying `%c'\n", process->champion->name, value);
	process->carry = (value == 0) ? 1 : 0;
}
