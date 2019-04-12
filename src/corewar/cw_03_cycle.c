/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_03_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:46:04 by jdouniol          #+#    #+#             */
/*   Updated: 2019/04/12 15:31:44 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"

static size_t	check_lives(t_process **process_list, t_process *process, \
				t_process *prev)
{
	t_process	*tmp;
	size_t		nb_lives;

	nb_lives = 0;
	while (process)
	{
		if (process->live_counter == 0)
		{
			tmp = process;
			if (prev != NULL)
				prev->next = process->next;
			else
				*process_list = process->next;
			process = process->next;
			free(tmp);
		}
		else
		{
			nb_lives += process->live_counter;
			process->live_counter = 0;
			prev = process;
			process = process->next;
		}
	}
	return (nb_lives);
}

int				check_is_alive(t_vm *vm)
{
	size_t		nb_lives;

	vm->nb_check += 1;
	nb_lives = check_lives(&vm->process, vm->process, NULL);
	if (nb_lives >= NBR_LIVE || vm->nb_check >= MAX_CHECKS)
	{
		if (vm->nb_check >= MAX_CHECKS)
			vm->nb_check = 0;
		vm->size_cycle -= CYCLE_DELTA;
	}
	if (nb_lives == 0 || vm->size_cycle <= 0 || vm->process == NULL)
		return (0);
	return (1);
}
