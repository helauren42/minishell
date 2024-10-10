/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodetest2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:21:31 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 19:29:39 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_preparse	*create_preparse_node(char *s, int quote)
{
	t_preparse	*node;

	node = (t_preparse *)malloc(sizeof(t_preparse));
	if (node)
	{
		node->s = ft_strdup(s);
		if (node->s == NULL)
		{
			free(node);
			return (NULL);
		}
		node->quote = quote;
		node->next = NULL;
	}
	return (node);
}
