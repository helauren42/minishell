/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_arrdress_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:50:06 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 13:51:08 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_addr(int **addr)
{
	int	i;

	i = 0;
	while (addr[i][0] != -1)
	{
		printf("addr[%d][0] = %d, addr[%d][1] = %d", i, addr[i][0], i,
			addr[i][1]);
		i++;
	}
}

int	find_next_word(char *read, int i)
{
	if (i > 0 && (read[i - 1] == '<' || read[i - 1] == '>' 
			|| read[i - 1] == '|'))
	{
		return (i);
	}
	while (read[i])
	{
		if (read[i] != ' ')
			return (i);
		i++;
	}
	if (read[i] == 0)
		return (0);
	return (i);
}
