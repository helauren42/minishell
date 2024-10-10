/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:18:39 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:49:52 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_preparse	*first_preparse(t_preparse *preparse, t_data *data)
{
	data->t->first = tokenize_this(preparse, data, 1, NULL);
	if (data->t->first == NULL)
		return (NULL);
	data->t->left = data->t->first;
	if (preparse != NULL)
		preparse = preparse->next;
	return (preparse);
}
