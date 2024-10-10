/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:51:25 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 21:48:01 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_temp	*tokenz_null(t_temp *first)
{
	free_tokenz(first);
	return (NULL);
}

char	*error_null(char *s)
{
	printf("%s", s);
	return (NULL);
}

t_redir	*error_null_redir(char *s)
{
	printf("%s", s);
	return (NULL);
}

int	error_one(char *s)
{
	printf("%s", s);
	return (1);
}

void	error_none(char *s)
{
	printf("%s", s);
}
