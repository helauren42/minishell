/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:01:14 by helauren          #+#    #+#             */
/*   Updated: 2023/11/04 15:40:19 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_execve(char ***s)
{
	int		i;
	char	**ret;

	i = 0;
	while (s[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (s[i] && s[i][2] != NULL && ft_strcmp(s[i][2], "env") == 0)
	{
		ret[i] = ft_strdup(s[i][0]);
		ret[i] = ft_strjoin(ret[i], "=");
		if (s[i][1] != NULL && s[i][1][0] != 0)
			ret[i] = ft_strjoin(ret[i], s[i][1]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
