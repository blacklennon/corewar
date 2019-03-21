/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by llopez            #+#    #+#             */
/*   Updated: 2019/03/19 18:46:28 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

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

char	*get_new_path(char *path)
{
	char	*newpath;
	int		i;

	i = ft_strlen(path);
	while (path[i] != '.')
		i--;
	newpath = malloc(sizeof(char) * (i + 5));
	ft_strncpy(newpath, path, i);
	newpath[i] = 0;
	ft_strcat(newpath, ".cor");
	return (newpath);
}

char		*get_name(char	**data)
{
	int	i;
	int	b;
	int	length;
	char	*line;

	b = 0;
	i = 0;
	length = 0;
	if (!data)
		return (NULL);
	while (data[i] && ft_strcmp(NAME_CMD_STRING, data[i]))
		i++;
	if (data[i] && !ft_strcmp(NAME_CMD_STRING, data[i]))
	{
		i++;
		if (data[i][0] != '"')
			return (NULL);
		while (data[i + b])
		{
			if (length > 0 && ft_strchr(data[i + b], '"'))
				break;
			length += ft_strlen(data[i + b]);
			b++;
		}
		length = length - 2;
		printf("\nname length : %d\n", length);
		line = ft_strnew(length);
		//ft_bzero(line, length);
		while (i <= b)
		{
			ft_strcat(line, data[i++]);
			ft_strcat(line, " ");
		}
		printf("%s\n", line);
		return (line);
	}
	return (NULL);
}

int		write_in_file(char *path, char **data)
{
	int		fd;
	char		*newpath;
	uint8_t		tmp[4];
	uint32_t	*table;
	char		*champ_name;

	champ_name = get_name(data);
	newpath = get_new_path(path);
	if ((fd = open(newpath, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)))
	{
		printf("output file : %s\n", newpath);
		bytes_conv((uint32_t)COREWAR_EXEC_MAGIC, tmp);
		write(fd, tmp, 4);
		write(fd, champ_name, ft_strlen(champ_name));
		free(champ_name);
		table = interpret(data, fd);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	char	*file;
	char	**data;
	uint8_t	binary[1024] = {0};
	int	i;

	(void)binary;
	i = 0;
	file = NULL;
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	file = read_file(argv[1]);
	data = split_whitespaces(file);
	while (data[i])
	{
		printf("%s\n", data[i]);
		i++;
	}
	write_in_file(argv[1], data);
	while (data[i])
		free(data[i++]);
	return (EXIT_SUCCESS);
}
