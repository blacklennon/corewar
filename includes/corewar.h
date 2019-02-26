/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:10:01 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/26 19:13:19 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "typedefs/s_process.h"

int			main(int ac, char **av);
void		init_vm(t_vm *vm);
void		mem_dump(uint8_t *p, size_t size);
void		load_champs(t_vm *vm);
uint32_t	swap_uint32(uint32_t value);

#endif