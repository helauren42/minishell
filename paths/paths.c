/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:48:38 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:49:27 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*whole_path(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 5;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(&s[i]) + 1));
	while (s[i])
	{
		ret[j] = s[i];
		j++;
		i++;
	}
	ret[j] = 0;
	return (ret);
}

char	**get_paths(t_data *data)
{
	int		i;
	char	**ret;
	char	*path_var;

	i = 0;
	while (data->exp_var[i])
	{
		if (ft_strcmp(data->exp_var[i][0], "PATH") == 0)
		{
			if (data->exp_var[i][1] == NULL)
				return (NULL);
			path_var = whole_path(data->exp_var[i][1]);
			ret = ft_split(path_var, ':');
			free(path_var);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char **split_paths, char *cmmd)
{
	int		i;
	char	*path;

	i = 0;
	while (split_paths[i])
	{
		path = ft_strjoin_nofree(split_paths[i], "/");
		path = ft_strjoin(path, cmmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	if (path != NULL)
		free(path);
	return (NULL);
}
