/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:33:10 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:47:10 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_init_av(t_data *data)
{
	int	i;

	if (data->init_av == NULL)
		return ;
	i = 0;
	while (data->init_av[i])
	{
		free(data->init_av[i]);
		i++;
	}
	free(data->init_av);
}

void	tokenization_fail2(void)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (j < 1)
	{
		i++;
	}
}

void	tokenization_fail(char *s)
{
	if (ft_strlen(s) > 2)
	{
		if (s[0] == '.' && s[1] == '\'')
		{
			printf("./minihell: %s: No such file or directory\n", s);
			return ;
		}
	}
	else if (ft_strlen(s) == 2)
	{
		if (s[0] == '.' && s[1] == '\'')
		{
			printf("./minihell: %s: No such file or directory\n", s);
			return ;
		}
	}
	printf("%s: command not found\n", s);
	g_exit_status = 127;
}
