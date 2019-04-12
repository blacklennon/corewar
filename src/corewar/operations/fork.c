/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:21:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 13:28:23 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "corewar.h"

/*
**	La fonction fork_process nous permet de copier l'ensemble des valeurs
**	du process copie grace a ft_memcpy, elle est utile pour fork et lfork
*/

static t_process	*fork_process(t_process *process)
{
	t_process	*new_process;

	if ((new_process = (t_process*)malloc(sizeof(t_process))) == NULL)
		crash(process, "Fork failed :(");
	ft_memcpy(new_process, process, sizeof(t_process));
	return (new_process);
}

/*
**	La fonction op_fork realise un fork du processus qui l'appelle
**	et charge ces valeurs a l'adresse envoyee en parametre
**	avec le modulo IDX_MOD qui en limite la portee
*/

void				op_fork(t_process *process, t_args *args)
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

void				op_lfork(t_process *process, t_args *args)
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
