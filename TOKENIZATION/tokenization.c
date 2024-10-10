/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:56:55 by helauren          #+#    #+#             */
/*   Updated: 2023/11/08 12:57:35 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	path_is_man(t_temp *left, t_cmd *man, char *s)
{
	t_cmd	*cmd;

	if (left == NULL || ft_strcmp(left->type, "cmd") != 0)
		return (0);
	cmd = (t_cmd *)left;
	if ((cmd->cmd_options[0] != NULL) && ft_strcmp(cmd->cmd_options[0],
			"man") == 0)
	{
		man->cmd_options = ft_strdup2d(man->cmd_options, s);
		return (1);
	}
	return (0);
}

char	*no_backslash(char *s, int i)
{
	while (s[i + 1])
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = 0;
	return (s);
}

void	decoy_out(t_temp *before_decoy, t_temp **right)
{
	free((*right)->type);
	free(*right);
	*right = before_decoy;
}

t_temp	*tokenization(t_preparse *preparse, t_data *data)
{
	preparse = first_preparse(preparse, data);
	while (preparse != NULL)
	{
		if (path_is_man(data->t->left, (t_cmd *)data->t->left,
				preparse->s) == 1)
			return (data->t->first);
		data->t->right = tokenize_this(preparse, data, 0, data->t->left);
		if (data->t->right == NULL)
			tokenz_null(data->t->first);
		if (ft_strcmp(data->t->right->type, "decoy") == 0)
		{
			decoy_out(data->t->before_decoy, &(data->t->right));
			preparse = preparse->next;
			continue ;
		}
		else
			data->t->before_decoy = data->t->right;
		data->t->right->left = data->t->left;
		data->t->left->right = data->t->right;
		data->t->left = data->t->right;
		preparse = preparse->next;
	}
	return (data->t->first);
}
