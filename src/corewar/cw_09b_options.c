/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_09b_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:42:57 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/09 19:02:11 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	add_player(char *file_path, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		if (vm->champions[i].file_path == NULL)
		{
			vm->champions[i].file_path = file_path;
			return ;
		}
		i++;
	}
	crash(NULL, "too many players");
}

void		try_add_player(char **av, int i, t_vm *vm)
{
	if (ft_strstr(av[i], ".cor") != NULL)
		add_player(av[i], vm);
	else
		crash(NULL, NULL);
}
