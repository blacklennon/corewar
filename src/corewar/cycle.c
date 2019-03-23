/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:46:04 by jdouniol          #+#    #+#             */
/*   Updated: 2019/03/23 20:22:02 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_is_alive(t_vm *vm)
{
	size_t	i;
	size_t	nb_lives;

	i = vm->nb_champs;
	vm->nb_check += 1;
	nb_lives = 0;
	while(i-- > 0)
	{
		nb_lives += vm->champions[i].live_counter;
		vm->champions[i].live_counter = 0;
	}
	if (nb_lives >= NBR_LIVE || vm->nb_check >= MAX_CHECKS)
	{
		if (vm->nb_check >= MAX_CHECKS)
			vm->nb_check = 0;
		vm->size_cycle -= CYCLE_DELTA;
	}
	else if (nb_lives == 0)
		return (0);
	return (1);
}
