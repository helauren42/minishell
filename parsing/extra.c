/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:30:42 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/06 20:51:45 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_len(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' ' && s[i] != '$')
	{
		len++;
		i++;
	}
	return (len);
}

void	get_var(char *s, int i, char *var)
{
	int	j;

	j = 0;
	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' ' && s[i] != '$')
	{
		var[j] = s[i];
		j++;
		i++;
	}
	var[j] = 0;
}

int	words_minus1(int **addr)
{
	int	i;

	i = 0;
	while (addr[i][0] != -1)
		i++;
	return (i);
}
