/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenzzzz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:17:28 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 13:33:12 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	to_decoy(t_temp *left, t_preparse *preparse, int redir)
{
	if (left != NULL && ft_strcmp(left->type, "exec") == 0)
		return (0);
	if (left != NULL && ft_strcmp(left->type, "cmd") == 0
		&& (preparse->s[0] == '.' || redir == 0))
		return (0);
	return (1);
}

t_temp	*decoyed(t_temp *left, t_preparse *preparse, int redir)
{
	if (left != NULL && ft_strcmp(left->type, "exec") == 0)
	{
		tokenize_as_option_arg(left, preparse);
		return ((t_temp *)decoy_it());
	}
	if (left != NULL && ft_strcmp(left->type, "cmd") == 0
		&& (preparse->s[0] == '.' || redir == 0))
	{
		tokenize_as_option_arg(left, preparse);
		return ((t_temp *)decoy_it());
	}
	return (NULL);
}

t_temp	*tokenize_this(t_preparse *preparse, t_data *data, int first,
		t_temp *left)
{
	int		redir;
	char	*cmd_path;

	redir = is_redir(preparse->s);
	if (to_decoy(left, preparse, redir) == 0)
		return (decoyed(left, preparse, redir));
	cmd_path = is_cmd(preparse->s, data);
	if (redir != 0 && preparse->quote == 0)
		return ((t_temp *)redir_it(redir, data));
	else if (is_exec(preparse->s) == 0 && preparse->quote == 0)
		return ((t_temp *)exec_it(preparse->s, data));
	else if (cmd_path)
		return ((t_temp *)cmd_it(preparse->s, data, cmd_path));
	if (first == 1)
	{
		tokenization_fail(preparse->s);
		return (NULL);
	}
	tokenize_as_option_arg(left, preparse);
	return ((t_temp *)decoy_it());
}
