/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:54:09 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 20:46:09 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_cd(char *read)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (read[i] != '\0')
	{
		if (read[i] == ' ')
		{
			i++;
			ret = &read[i];
			break ;
		}
		i++;
	}
	return (ret);
}

char	*get_home_directory(t_data *data)
{
	char	*home;

	home = get_env_value(data, "HOME");
	if (home)
		return (home);
	else
	{
		perror("getenv");
		free(home);
		return (NULL);
	}
}

int	find_index(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->exp_var[i][0])
	{
		if (strcmp(data->exp_var[i][0], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	space(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}
