/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:29:00 by helauren          #+#    #+#             */
/*   Updated: 2023/11/04 18:29:44 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_s(int *addr, char *read)
{
	int		start;
	int		end;
	char	*ret;
	int		i;

	i = 0;
	start = addr[0];
	end = addr[1];
	ret = malloc(sizeof(char) * (end - start) + 2);
	while (start <= end)
	{
		ret[i] = read[start];
		start++;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	**make_split(t_data *data, int **addr, char *read, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		data->init_av[i] = extract_s(addr[i], read);
		i++;
	}
	data->init_av[i] = NULL;
	return (data->init_av);
}

void	output_first_parse(t_data *data)
{
	int	i;

	i = 0;
	while (data->init_av[i])
	{
		printf("%s\n", data->init_av[i]);
		i++;
	}
}

void	free_addr(int **addr, int len)
{
	int	i;

	i = 0;
	while (i <= len && addr[i] != NULL)
	{
		free(addr[i]);
		i++;
	}
	free(addr);
}

void	init_to_strings(t_data *data, char *read)
{
	int	**addr;
	int	words;
	int	len;

	len = 0;
	addr = words_addr(read, &len);
	words = words_minus1(addr);
	data->init_av = malloc(sizeof(char **) * (words + 1));
	make_split(data, addr, read, words);
	free_addr(addr, len);
	read = NULL;
}
