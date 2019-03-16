/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitwhitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:55:03 by llopez            #+#    #+#             */
/*   Updated: 2019/03/16 15:00:16 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../lib/libft/includes/libft.h"
#include "asm.h"

char	**split_whitespaces(char *txt)
{
	char	**table;
	int		count_words;
	int		i;
	int		length;

	length = 0;
	i = -1;
	count_words = 0;
	if (!txt)
		return (NULL);
	while (txt[++i])
	{
		if (ft_strchr(" \t\n", txt[i]))
			continue;
		count_words++;
		while (!ft_strchr(" \t\n", txt[i + 1]))
			i++;
	}
	table = (char **)malloc(sizeof(char *) * count_words + 2);
	i = -1;
	count_words = 0;
	while (txt[++i])
	{
		if (ft_strchr(" \t\n", txt[i]))
		{
			if (length)
			{
				table[count_words] = (char *)malloc(sizeof(char) * length + 1);
				ft_strncpy(table[count_words], &txt[i - length], length);
				table[count_words][length] = 0;
				printf("%s\n", table[count_words]);
				length = 0;
				count_words++;
			}
			continue;
		}
		length++;
	}
	table[count_words] = NULL;
	return (table);
}
