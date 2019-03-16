/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by llopez            #+#    #+#             */
/*   Updated: 2019/03/16 18:00:12 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "asm.h"

char	*read_file(char	*path)
{
	int		fd;
	int		i;
	char	buff[4096];
	char	*tmp;
	char	*content;

	i = 0;
	tmp = NULL;
	content = NULL;
	if ((fd = open(path, O_RDONLY)))
	{
		while ((i = read(fd, buff, 4096)))
		{
			buff[i] = 0;
			if (i && content && ft_strlen(content))
			{
				if (tmp)
					free(tmp);
				tmp = ft_strdup(content);
				if (content)
					free(content);
				content = (char *)malloc((i + ft_strlen(tmp) + 1));
				content = ft_strcpy(content, tmp);
				content = ft_strcat(content, buff);
			}
			else if (i)
				content = ft_strdup(buff);
			if (i < 4096)
				return (content);
		}
	}
	return (content);
}

int		check_args(int argc, char **argv)
{
	if (argc >= 2 && open(argv[1], O_RDONLY) > 0)
		return (1);
	return (0);
}

int32_t	swap_int32(int32_t value)
{
	value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
	return ((value << 16) | ((value >> 16) & 0xFFFF));
}

uint8_t	*bytes_conv(uint32_t content, uint8_t *table)
{
	(*(uint32_t*)table) = (uint32_t)swap_int32(content);
	return (table);
}

int		write_in_file(char *path)
{
	int		fd;
	char	*newpath;
	int		i;
	uint8_t	tmp[4];

	i = ft_strlen(path);
	while (path[i] != '.')
		i--;
	printf("%d (%c)\n", i, path[i]);
	newpath = malloc(sizeof(char) * (i + 5));
	ft_strncpy(newpath, path, i);
	newpath[i] = 0;
	printf("just path without extension : %s\n", newpath);
	ft_strcat(newpath, ".cor");
	printf("output file : %s (size: %zu | malloc: %d)\n", newpath, \
			ft_strlen(newpath), i + 4);
	if ((fd = open(newpath, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)))
	{
		printf("output file in %s created\nFilling file\n", newpath);
		printf("MAGIC : %x\n", COREWAR_EXEC_MAGIC);
		bytes_conv((uint32_t)COREWAR_EXEC_MAGIC, tmp);
		write(fd, tmp, 4);
		i = PROG_NAME_LENGTH - ft_strlen("name");
		while (i >= 0)
		{
			write(fd, bytes_conv((uint32_t)0x0, tmp), 1);
			i--;
		}
		write(fd, bytes_conv((uint32_t)0x0, tmp), 4);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	char	*file;
	char	**data;

	file = NULL;
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	file = read_file(argv[1]);
	write_in_file(argv[1]);
	data = split_whitespaces(file);
	//interpret();
	return (EXIT_SUCCESS);
}
