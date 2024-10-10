/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:07:41 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:58:56 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_cd_option_without_previous_path(t_data *data)
{
	free(data->pwd);
	data->pwd = NULL;
	return (1);
}

int	process_cd_option(char *path, t_data *data)
{
	(void)path;
	if (data->previous_path != NULL)
		return (process_cd_option_with_previous_path(data));
	else
		return (process_cd_option_without_previous_path(data));
	return (0);
}

void	fuu_uuck(t_data *data)
{
	if (data->pwd != NULL)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
}

int	change_working_dir(char *path, t_data *data, int tilde, int nil)
{
	char	*otherpath;

	if (data->pwd != NULL)
		data->old_pwd = data->pwd;
	data->pwd = find_pwd();
	if (path != NULL && strcmp(path, "-") == 0)
		return (process_cd_option(path, data));
	else
	{
		otherpath = expand_tilde(path, data, &tilde, &nil);
		if (process_cd(otherpath, data) != 0)
		{
			fuu_uuck(data);
			return (1);
		}
		if (data->previous_path != NULL)
		{
			free(data->previous_path);
			data->previous_path = NULL;
		}
		data->previous_path = data->pwd;
		if (tilde == 0 || nil == 0)
			free(otherpath);
	}
	return (0);
}

int	exec_cd(char *read, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (change_working_dir(parse_cd(read), data, i, j) != 0)
		return (1);
	return (1);
}
