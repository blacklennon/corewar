/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by llopez            #+#    #+#             */
/*   Updated: 2019/03/14 17:03:15 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char	*read_file(char	*path, char	*content)
{
	int		fd;
	int		index;
	int		i;

	i = 0;
	index = 0;
	if ((fd = open(path, O_RDONLY)))
	{
		while ((i = read(fd, &content[index], 4096)))
		{
			index += i;
			content[index + 1] = 0;
			if (i < 4096)
				return (content);
		}
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	char	file[4096];

	//if (!check_args(argc, argv))
	//	return (EXIT_FAILURE);
	read_file(argv[1], file);
	printf("%s\n", file);
	return (EXIT_SUCCESS);
}
