/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:32:03 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/27 00:48:14 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "corewar.h"

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
		crash(process, "This should never been reached op3.c:31");
	value = read4_memory(get_vm(NULL), process->program_counter + address);
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
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
	if (vm->verbose >= 2)
	{
		ft_printf("Player N %d is doing LLD\n", process->champion->id);
		if (vm->verbose == 3)
			ft_printf("Value of LLD : %d loaded in reg %d\n",\
				result, args->value[1].u_reg);
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
	t_vm	*vm;

	vm = get_vm(NULL);
	value = (char)(process->registers[args->value[0].u_reg] % 256);
	ft_printf("Process %s is saying `%c'\n", process->champion->name, value);
	process->carry = (value == 0) ? 1 : 0;
	if (vm->verbose >= 2)
		ft_printf("Player N %d is doing AFF\n", process->champion->id);
}
