/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:26:09 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/05 19:58:38 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(char *s)
{
	if (s == NULL || ft_strlen(s) < 1)
		return (0);
	if (ft_strlen(s) == 1)
	{
		if (s[0] == '<')
			return (1);
		if (s[0] == '>')
			return (3);
		if (s[0] == '|')
			return (5);
	}
	if (ft_strlen(s) == 2)
	{
		if (s[0] == '<' && s[1] == '<')
			return (2);
		if (s[0] == '>' && s[1] == '>')
			return (4);
	}
	return (0);
}

t_redir	*redir_it(int sign, t_data *data)
{
	t_redir	*redir;

	(void)data;
	redir = malloc(sizeof(t_redir));
	redir->type = ft_strdup("redir");
	redir->sign = sign;
	redir->left = NULL;
	redir->right = NULL;
	data->buffer = NULL;
	if (sign == 2)
		redir->delim = NULL;
	if (sign == 5)
	{
		if (pipe(redir->pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (redir);
}

int	is_exec(char *s)
{
	if (s == NULL)
		return (1);
	if (ft_strlen(s) <= 2)
		return (1);
	if (s[0] == '.' && s[1] == '/')
		return (0);
	if (s[0] == '.' && s[1] == '.' && s[2] == '/')
		return (0);
	return (1);
}

t_exec	*exec_it(char *s, t_data *data)
{
	t_exec	*ex;

	if (ft_strncmp(s, "./minishell", ft_strlen("./minishell")) == 0)
		return (NULL);
	ex = malloc(sizeof(t_exec));
	ex->sign = 0;
	ex->type = ft_strdup("exec");
	ex->path = find_exec_path(s, data);
	if (ex->path == NULL)
	{
		free(ex->type);
		free(ex);
		return (NULL);
	}
	ex->options = malloc(sizeof(char *) * 2);
	ex->options[0] = ft_strdup(s);
	ex->options[1] = NULL;
	ex->left = NULL;
	ex->right = NULL;
	return (ex);
}
