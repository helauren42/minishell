/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:31:59 by helauren          #+#    #+#             */
/*   Updated: 2023/11/05 19:22:09 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_whole_file(char *file)
{
	int		br;
	char	*buff;
	char	*red;
	int		fd;

	fd = open(file, O_RDONLY, 0644);
	br = 1;
	red = NULL;
	buff = malloc(sizeof(char) * 10);
	while (br > 0)
	{
		br = read(fd, buff, 9);
		buff[br] = 0;
		red = ft_strjoin(red, buff);
	}
	return (red);
}

int	has_new_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
