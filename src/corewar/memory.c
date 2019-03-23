/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:49:53 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/23 23:57:16 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int32_t			read4_memory(t_vm *vm, size_t index)
{
	int32_t		*tmp;
	uint8_t		tab[4];
	size_t		i;

	index %= MEM_SIZE;
	if (MEM_SIZE - index > 4)
		tmp = (int32_t*)&vm->memory[index];
	else
	{
		tmp = (int32_t*)tab;
		i = 0;
		ft_bzero(tab, sizeof(tab));
		while (i < 4)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
	}
	return (swap_int32(*tmp));
}

int16_t			read2_memory(t_vm *vm, size_t index)
{
	int16_t		*tmp;
	uint8_t		tab[2];
	size_t		i;

	index %= MEM_SIZE;
	if (MEM_SIZE - index > 2)
		tmp = (int16_t*)&vm->memory[index];
	else
	{
		tmp = (int16_t*)tab;
		i = 0;
		ft_bzero(tab, sizeof(tab));
		while (i < 2)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
	}
	return (swap_int16(*tmp));
}

int8_t		read1_memory(t_vm *vm, size_t index)
{
	index %= MEM_SIZE;
	return ((int8_t)vm->memory[index]);
}

void		write4_memory(t_vm *vm, int32_t value, size_t index)
{
	int32_t		*tmp;
	uint8_t		tab[4];
	size_t		i;

	tmp = (int32_t*)tab;
	*tmp = swap_int32(value);
	i = 0;
	while (i < 4)
	{
		index %= MEM_SIZE;
		vm->memory[index] = tab[i];
		index++;
		i++;
	}
}

void		write2_memory(t_vm *vm, int16_t value, size_t index)
{
	uint8_t		tab[2];
	size_t		i;

	*((int16_t*)tab) = swap_int16(value);
	i = 0;
	while (i < 2)
	{
		index %= MEM_SIZE;
		vm->memory[index] = tab[i];
		index++;
		i++;
	}
}