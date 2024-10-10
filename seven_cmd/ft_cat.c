/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:31:59 by helauren          #+#    #+#             */
/*   Updated: 2023/11/05 19:21:57 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_one_line(int fd)
{
	char	*buff;
	char	*s;
	int		br;

	br = 1;
	s = NULL;
	buff = malloc(sizeof(char) * 10);
	while (br > 0)
	{
		br = read(fd, buff, 9);
		buff[br] = 0;
		s = ft_strjoin(s, buff);
		if (has_new_line(s) == 0)
			break ;
	}
	free(buff);
	return (s);
}

int	ft_cat(char **option)
{
	char	*buff;
	int		len;

	(void)option;
	buff = read_one_line(STDIN_FILENO);
	len = strlen(buff) - 1;
	buff[len] = 0;
	printf("%s\n", buff);
	free(buff);
	return (1);
}

void	redir_cat_out(t_redir *first)
{
	t_redir	*redir;

	redir = first;
	while (redir->right != NULL)
		redir = (t_redir *)redir->right;
	while (ft_strcmp(redir->type, "redir"))
		redir = (t_redir *)redir->left;
	if (redir->sign == 5)
		dup2(redir->pipe_fd[1], STDOUT_FILENO);
	if (redir->sign == 4 || redir->sign == 3)
		dup2(redir->file_fd, STDOUT_FILENO);
}

int	prepare_cat(char **option, t_temp *first)
{
	t_redir	*redir;
	t_cmd	*cmd;

	redir = (t_redir *)first;
	while (1)
	{
		if (redir->right != NULL)
			cmd = (t_cmd *)redir->right;
		if (redir->sign != 5 && (ft_strcmp(cmd->type, "cmd")
				|| ft_strcmp(cmd->cmd_options[0], "cat")))
			break ;
		if (redir->sign == 5)
		{
			if (ft_strcmp(cmd->type, "cmd") || ft_strcmp(cmd->cmd_options[0],
					"cat"))
				break ;
		}
		redir = (t_redir *)redir->right;
		if (redir == NULL)
			break ;
	}
	redir_cat_out((t_redir *)first);
	ft_cat(option);
	return (1);
}
