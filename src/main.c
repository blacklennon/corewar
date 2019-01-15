/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:41:32 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/15 16:12:04 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "get_next_line.h"
#include "label.h"
#include "parser.h"
#include "utils.h"
#include "op.h"

static int		read_file(int fd)
{
	int			ret;
	char		*line;
	t_header	header;
	t_label		*label_list;

	ret = 0;
	label_list = NULL;
	header.magic = COREWAR_EXEC_MAGIC;
	errno = 0;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1 || parse_line(line, &header, &label_list))
		{
			if (ret == -1)
				perror("asm");
			free(line);
			return (1);
		}
		free(line);
		errno = 0;
	}
	free(line);
	while (label_list)
	{
		printf("Label: %s\n", label_list->name);
		label_list = label_list->next;
	}
	return (0);
}

static int		file_handler(char *file_path)
{
	int			fd;
	int			ret;

	errno = 0;
	if ((fd = open(file_path, O_RDONLY)) < 0)
	{
		perror("asm");
		return (1);
	}
	ret = read_file(fd);
	close(fd);
	return (ret);
}

int				main(int ac, char **av)
{
	int			i;
	int			ret;

	if (ac < 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	i = 1;
	ret = 0;
	while (i < ac)
	{
		ret += file_handler(av[i]);
		i++;
	}
	return (ret ? EXIT_FAILURE : EXIT_SUCCESS);
}