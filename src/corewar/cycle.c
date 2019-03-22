/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:46:04 by jdouniol          #+#    #+#             */
/*   Updated: 2019/03/22 12:35:42 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int no_process_is_alive(t_vm *vm) // check qu aucun joueur n a fait de live a la fin d un cycle
{
    int i;

    i = MAX_PLAYERS; // MAX PLAYERS + nb fork?
    while(i-- > 0)
    {
        if (vm->process[i].is_alive == 1)
            return (0);
    }
    if (i == 0)
        return (1);
    else
        return(0);
    
}

/*
**  Check after cycle se declenche a chaque fois que le compteur cycle se termine
**  
**
*/

void check_after_cycle(t_vm *vm)
{
    int i;

    i = MAX_PLAYERS; // max_players + fork?
    if (vm->live_counter_temp >= NBR_LIVE || vm->nb_check >= MAX_CHECKS)
    {
        vm->size_cycle -= CYCLE_DELTA;
        while(i-- > 0)
            vm->process[i].is_alive = 0;
        vm->someone_is_alive = 0;
        vm->live_counter_temp = 0;
        vm->nb_check = 0;
    }
    else
    {
        /* je ne crois pas qu il y ait de else */
    }
    
}
