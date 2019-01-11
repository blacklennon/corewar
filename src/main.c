/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:41:32 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/11 16:08:58 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "op.h"

int		main(int ac, char **av)
{
	t_header	header;
	int			fd;
	int			ret;
	char		*line;

	if (ac <= 1 || (fd = open(av[1], O_RDONLY)) <= -1)
		return (EXIT_FAILURE);
	header.magic = COREWAR_EXEC_MAGIC;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1 || parse_line(line, &header))
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}