/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:48:23 by helauren          #+#    #+#             */
/*   Updated: 2023/11/04 15:43:32 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_hd(t_data *data)
{
	if (data->free_hd == 1)
	{
		free_double_str(data->buffer);
		data->buffer = NULL;
		data->free_hd = 0;
	}
}
