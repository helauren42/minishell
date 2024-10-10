/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:47:05 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 14:47:05 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	out_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->exp_var[i])
	{
		if (data->exp_var[i][0] && data->exp_var[i][1]
			&& data->exp_var[i][0][0] != '\0' && data->exp_var[i][1][0] != '\0')
			printf("%s=%s\n", data->exp_var[i][0], data->exp_var[i][1]);
		i++;
	}
	return (1);
}
