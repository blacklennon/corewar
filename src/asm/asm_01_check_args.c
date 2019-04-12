/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_01_check_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by jdouniol          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/12 12:56:17 by llopez           ###   ########.fr       */
=======
/*   Updated: 2019/04/12 13:12:08 by jdouniol         ###   ########.fr       */
>>>>>>> d62571b6833f9a996714e78d73553c355227d465
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "common.h"
#include "op.h"
#include "asm.h"

int		check_extension(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	if (i >= 2 && path[i] == 's' && path[i - 1] == '.')
		return (1);
	return (0);
}

int		check_args(char *file_path)
{
	int		fd;

	if (check_extension(file_path) == 0)
	{
		ft_printf("asm: %s: Bad extension\n", file_path);
		exit(EXIT_FAILURE);
	}
	errno = 0;
	if ((fd = open(file_path, O_RDONLY)) < 0)
	{
		ft_printf("asm: %s: %s\n", file_path, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (fd);
}
