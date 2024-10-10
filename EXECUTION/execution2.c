/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:41:19 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/05 15:59:01 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	send_to_pipe(t_data *data)
{
	int	i;

	i = 0;
	dup2(data->hd_pipe_fd[1], STDOUT_FILENO);
	while (data->buffer[i])
	{
		printf("%s\n", data->buffer[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

void	prepare_hd_pipe(t_data *data)
{
	pid_t	pid;

	data->free_hd = 1;
	if (pipe(data->hd_pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		send_to_pipe(data);
	close(data->hd_pipe_fd[1]);
	dup2(data->og_stdout, STDOUT_FILENO);
}
