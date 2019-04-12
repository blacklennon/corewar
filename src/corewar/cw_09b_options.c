/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_09b_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:42:57 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 18:35:22 by jdouniol         ###   ########.fr       */
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
	crash(NULL, "Too many players");
}

void		try_add_player(char *file_path, t_vm *vm)
{
	size_t	len;

	len = ft_strlen(file_path) - 1;
	if (len < 4 || file_path[len--] != 'r' || file_path[len--] != 'o'\
		|| file_path[len--] != 'c' || file_path[len] != '.')
		crash(NULL, "Invalid file");
	else
		add_player(file_path, vm);
}
