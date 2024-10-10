/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodetest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:48:44 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 18:21:48 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_to_preparse_list(t_preparse **head, char *s, int quote)
{
	t_preparse	*new_node;
	t_preparse	*current;

	new_node = create_preparse_node(s, quote);
	if (new_node)
	{
		if (*head == NULL)
			*head = new_node;
		else
		{
			current = *head;
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
		}
	}
}

void	free_preparse_list(t_preparse *head)
{
	t_preparse	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->s != NULL)
		{
			free(temp->s);
		}
		free(temp);
	}
}

// void	print_preparse_list(t_preparse *head)
// {
// 	t_preparse	*current;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		printf("String: \"%s\" Quote: \"%d\"\n", current->s, current->quote);
// 		current = current->next;
// 	}
// }

int	only_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

t_preparse	*strings_to_linked_list(t_data *data)
{
	int			i;
	int			val;
	t_preparse	*head;

	head = NULL;
	i = 0;
	val = 0;
	if (data->init_av[i] == NULL)
		return (NULL);
	while (data->init_av[i])
	{
		if (only_spaces(data->init_av[i]) == 0)
		{
			free(data->init_av[i]);
			i++;
			continue ;
		}
		val = what_quote(data->init_av[i]);
		append_to_preparse_list(&head, data->init_av[i], val);
		free(data->init_av[i]);
		i++;
	}
	free(data->init_av);
	data->init_av = NULL;
	return (head);
}
