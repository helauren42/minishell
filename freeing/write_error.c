/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:39:00 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:47:22 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_error(char *s)
{
	printf("%s\n", s);
}

void	error_unexpected_token(char c)
{
	if (c == '\n')
		printf("./minihell: syntax error near unexpected token `newline'\n");
	else
		printf("./minihell: syntax error near unexpected token `%c'\n", c);
}

void	find_var_error(char *read)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (read[i] == '=')
		i = 0;
	else
		while (read[i -1] != '=')
			i++;
	if (read[i] == '\"' || read[i] == '\'')
		i++;
	while (read[i + j] != '\"' && read[i + j] != '\'' && read[i + j])
		j++;
	if (read[i + j] == '\"' || read[i + j] == '\'')
		read[i + j] = 0;
	printf("./minihell: export: `%s': not a valid identifier ", &read[i]);
}
