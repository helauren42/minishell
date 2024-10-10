/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:37:20 by marvin            #+#    #+#             */
/*   Updated: 2023/07/08 11:37:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_next(char *stat)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == 0)
		return (NULL);
	i++;
	while (stat[i + j])
		j++;
	str = malloc (sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (stat[i + j])
	{
		str[j] = stat[i + j];
		j++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_line(char *stat)
{
	char	*str;
	int		i;

	i = 0;
	if (stat[i] == 0)
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	str = malloc (sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stat[i] != 0 && stat[i] != '\n')
	{
		str[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
		str[i++] = '\n';
	str[i] = 0;
	return (str);
}

char	*ft_read(int fd, char *stat)
{
	char	*buff;
	int		byteread;

	byteread = 1;
	while (!ft_strchr2(stat, '\n') && byteread != 0)
	{
		buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		byteread = read (fd, buff, BUFFER_SIZE);
		if (byteread == -1)
		{
			free (buff);
			buff = NULL;
			return (NULL);
		}
		buff[byteread] = '\0';
		stat = ft_strjoin2(stat, buff);
		free (buff);
		buff = NULL;
	}
	return (stat);
}

char	*get_next_line(int fd)
{
	static char	*stat[10240];
	char		*line;
	char		*next;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stat[fd] = ft_read(fd, stat[fd]);
	if (stat[fd] == NULL)
		return (NULL);
	line = ft_line(stat[fd]);
	next = stat[fd];
	stat[fd] = ft_next(stat[fd]);
	free (next);
	next = NULL;
	return (line);
}

// int main(void)
// {
// 	int 	fd1;
// 	int		fd2;
// 	char	*theline;

// 	fd1 = open ("first", O_RDONLY, 0777);
// 	fd2 = open ("second", O_RDONLY, 0777);
// 	if (fd1 == -1)
// 		printf("couldn't open");
// 	theline = get_next_line(fd1);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd1);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd2);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd1);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd1);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd2);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd2);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd2);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd1);
// 	printf("output = %s\n", theline);
// 	theline = get_next_line(fd2);
// 	printf("output = %s\n", theline);
// 	free (theline);
// 	return (0);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*theline = NULL;

// 	fd = open("toread", O_RDONLY, 0644);
// 	if (fd == -1)
// 		return (1);
// 	theline = get_next_line(fd);
// 	printf("first line output = %s\n", theline);
// 		free (theline);
// 	theline = get_next_line(fd);
// 	printf("second line output = %s\n", theline);
// 		free (theline);
// 	theline = get_next_line(fd);
// 	printf("third line output = %s\n", theline);
// 		free (theline);
// 	theline = get_next_line(fd);
// 	printf("fourth line output = %s\n", theline);
// 		free (theline);
// 	theline = get_next_line(fd);
// 	printf("fifth line output = %s\n", theline);
// 	theline = get_next_line(fd);
// 	printf("sixth line output = %s\n", theline);
// 	close(fd);
// 	free (theline);
// 	return (0);
// }