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

void			builtin_builtin(t_env *c)
{
	int		i;
	const char	error[] = SHELL_NAME": no such builtin: ";

	i = 0;
	if (!c->av[1])
		return ;
	c->ac--;
	while (c->av[i + 1])
	{
		c->av[i] = c->av[i + 1];
		i++;
	}
	c->av[i] = NULL;
	if (do_builtin(c) == 0)
	{
		// write(1, SHELL_NAME, sizeof(SHELL_NAME) -1);
		write(1, error, sizeof(error) - 1);
		write(1, c->av[0], ft_strlen(c->av[0]));
		write(1, "\n", 1);
	}
}