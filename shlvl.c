/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 11:59:12 by alanteri          #+#    #+#             */
/*   Updated: 2015/12/15 11:59:16 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		shlvl(t_env *c)
{
	char	**tmp;
	char	*lvl;
	int		int_lvl;

	if (!(lvl = get_env_value(c->my_env, "SHLVL")))
	{
		tmp = set_env_element(c->my_env, "SHLVL", "1");
		ft_tab_free(c->my_env);
		c->my_env = tmp;
	}
	else
	{
		int_lvl = ft_atoi(lvl + 6) + 1;
		lvl = ft_itoa(int_lvl);
		tmp = set_env_element(c->my_env, "SHLVL", lvl);
		free(lvl);
		ft_tab_free(c->my_env);
		c->my_env = tmp;
	}
}
