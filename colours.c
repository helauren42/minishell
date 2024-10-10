/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:00:13 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/01 17:01:03 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_text_color(int color_code)
{
	printf("\x1b[%dm", color_code);
}

void	reset_text_color(void)
{
	printf("\x1b[0m");
}

void	set_text_color_to_orange(void)
{
	printf("\x1b[38;5;208m");
}
