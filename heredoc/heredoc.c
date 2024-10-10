/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:18:27 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 21:49:50 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_heredoc(t_temp *heredoc)
{
	if (heredoc->right == NULL)
		return (0);
	while (heredoc->right && (heredoc->right->sign == 2
			|| heredoc->right->sign == 1))
	{
		if (heredoc->right->sign == 2)
			return (1);
		heredoc = heredoc->right;
	}
	return (0);
}

t_redir	*handle_heredoc_input(t_redir *heredoc, t_data *data)
{
	while (heredoc != NULL && (heredoc->sign == 2 || heredoc->sign == 1))
	{
		while (1)
		{
			if (heredoc->delim == NULL)
				return (error_null_redir("./minihell: syntax error \
				`newline\'\n"));
			data->hd_line = readline("\xF0\x9F\x8E\x83heredoc>\xF0\x9F\x8E\x83 ");
			if (data->hd_line == NULL || g_exit_status == 130)
				break ;
			if (ft_strcmp(data->hd_line, heredoc->delim) == 0)
			{
				free(data->hd_line);
				if (last_heredoc((t_temp *)heredoc) == 0)
					return (heredoc);
				break ;
			}
			if (last_heredoc((t_temp *)heredoc) == 0)
				data->buffer = ft_strdup2d(data->buffer, data->hd_line);
			free(data->hd_line);
		}
		heredoc = (t_redir *)heredoc->right;
	}
	return (heredoc);
}
