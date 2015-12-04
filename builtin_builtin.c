/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 19:59:12 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 19:59:16 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ERROR SHELL_NAME": no such builtin: "

void			builtin_builtin(t_env *c)
{
	int			i;
	const char	error[] = ERROR;

	i = 0;
	if (!c->av[1])
		return ;
	c->ac--;
	free(c->av[0]);
	while (c->av[i + 1])
	{
		c->av[i] = c->av[i + 1];
		i++;
	}
	c->av[i] = NULL;
	if (do_builtin(c) == 0)
	{
		write(1, error, sizeof(error) - 1);
		write(1, c->av[0], ft_strlen(c->av[0]));
		write(1, "\n", 1);
	}
}

void			launch_command(t_env *c)
{
	if (c->line && *c->line)
	{
		c->av = get_call_command(c->line);
		if (c->av && c->av[0])
		{
			if (!do_builtin(c))
			{
				if ((c->path = finding_bin(c)))
					exec_bin(c);
				else
					unknown_command(c);
			}
		}
		ft_tab_free(c->av);
	}
}
