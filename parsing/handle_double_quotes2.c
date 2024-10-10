/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_quotes2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:10:54 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/08 12:57:10 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dict_value(t_data *data, char *var)
{
	int	i;

	i = 0;
	if (ft_strcmp (var, "?") == 0)
		return (ft_itoa(g_exit_status));
	while (data->exp_var[i])
	{
		if (ft_strcmp(data->exp_var[i][0], var) == 0
			&& data->exp_var[i][1] != 0)
			return (ft_strdup(data->exp_var[i][1]));
		i++;
	}
	return (NULL);
}

int	even_bs_before(char *s, int i)
{
	int	count;

	count = 0;
	if (i == 0)
		return (1);
	i--;
	while (i >= 0 && s[i] == '\\')
	{
		if (s[i] == '\\')
			count++;
		i--;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

void	mid(int *j, char *dest, char *value)
{
	int	k;

	k = 0;
	while (value != NULL && value[k])
	{
		dest[*j] = value[k];
		(*j)++;
		k++;
	}
	free(value);
}
