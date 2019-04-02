/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_05c_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:31:34 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/02 17:26:18 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "corewar.h"

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
		crash(process, "This should never been reached op2.c:33");
	value = read4_memory(get_vm(NULL), \
	process->program_counter + (address % IDX_MOD));
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
}

/*
**	STI reste a commenter et a appliquer le verbose
*/

void		op_sti(t_process *process, t_args *args)
{
	int32_t	value_to_store;
	int32_t	address;

	address = 0;
	value_to_store = process->registers[args->value[0].u_reg];
	get_value_of_arg(process, &args->value[1], &args->type[1], STI);
	get_value_of_arg(process, &args->value[2], &args->type[2], STI);
	if (args->type[1] == e_result && args->type[2] == e_dir)
		address = args->value[1].u_dir32 + args->value[2].u_dir16;
	else if (args->type[1] == e_result && args->type[2] == e_result)
		address = args->value[1].u_dir32 + args->value[2].u_dir32;
	else if (args->type[1] == e_dir && args->type[2] == e_dir)
		address = args->value[1].u_dir16 + args->value[2].u_dir16;
	else if (args->type[1] == e_dir && args->type[2] == e_result)
		address = args->value[1].u_dir16 + args->value[2].u_dir32;
	else
		crash(process, "This should never been reached op2.c:60");
	write4_memory(get_vm(NULL), value_to_store, \
	process->program_counter + (address % IDX_MOD));
	process->carry = (value_to_store == 0) ? 1 : 0;
}

/*
**	La fonction fork_process nous permet de copier l'ensemble des valeurs
**	du process copie grace a ft_memcpy, elle est utile pour fork et lfork
*/

t_process	*fork_process(t_process *process)
{
	t_process	*new_process;

	if ((new_process = (t_process*)malloc(sizeof(t_process))) == NULL)
		crash(process, "fork failed :(");
	ft_memcpy(new_process, process, sizeof(t_process));
	return (new_process);
}

/*
**	La fonction op_fork realise un fork du processus qui l'appelle
**	et charge ces valeurs a l'adresse envoyee en parametre
**	avec le modulo IDX_MOD qui en limite la portee
*/

void		op_fork(t_process *process, t_args *args)
{
	t_vm		*vm;
	t_process	*new_process;

	args->value[0].u_dir16 %= IDX_MOD;
	new_process = fork_process(process);
	new_process->program_counter = (process->program_counter\
		+ args->value[0].u_dir16) % MEM_SIZE;
	vm = get_vm(NULL);
	new_process->next = vm->process;
	vm->process = new_process;
}

/*
**	La fonction op_lfork realise un fork du processus qui l'appelle
**	et charge ces valeurs a l'adresse envoyee en parametre
**	sans le modulo IDX_MOD qui en limiterait la portee
*/

void		op_lfork(t_process *process, t_args *args)
{
	t_vm		*vm;
	t_process	*new_process;

	new_process = fork_process(process);
	new_process->program_counter = (process->program_counter \
	+ args->value[0].u_dir16) % MEM_SIZE;
	vm = get_vm(NULL);
	new_process->next = vm->process;
	vm->process = new_process;
}
