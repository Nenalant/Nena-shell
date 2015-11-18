/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 20:03:27 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 20:03:28 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**set_env_element(char **env, char *key, char *value)
{
	int			i;
	int			j;

	j = 0;
	i = id_pos(env, key);
	if (i == -1)
	{
		env = ft_tab_copy_extand(env);
		while (env[j])
			j++;
		env[j] = new_env_line(key, value);
		env[j + 1] = NULL;
	}
	else
	{
		env = ft_tab_copy(env);
		free(env[i]);
		env[i] = new_env_line(key, value);
	}
	return (env);
}

void		builtin_env(t_env *c)
{
	const char	error[] = "env: Too many arguments.\n";

	if (c->ac > 1)
		write(1, error, sizeof(error) - 1);
	else
		put_string_tab(c->my_env);
}

void		builtin_setenv(t_env *c)
{
	int			j;
	char		**tmp;
	const char	error[] = "setenv: Too many arguments.\n";

	j = 0;
	if (c->ac > 3)
		write(1, error, sizeof(error) - 1);
	else if (!c->av[1])
	{
		put_string_tab(c->my_env);
		return ;
	}
	tmp = set_env_element(c->my_env, c->av[1], c->av[2]);
	ft_tab_free(c->my_env);
	c->my_env = tmp;
}

void		do_unsetenv(t_env *c, char *key)
{
	int		i;

	i = id_pos(c->my_env, key);
	if (i == -1)
		return ;
	free(c->my_env[i]);
	while (c->my_env[i + 1])
	{
		c->my_env[i] = c->my_env[i + 1];
		i++;
	}
	c->my_env[i] = NULL;
}

void		builtin_unsetenv(t_env *c)
{
	int			i;
	const char	error[] = "unsetenv: Too few arguments.\n";

	i = 1;
	if (c->ac < 2)
		write(1, error, sizeof(error) - 1);
	else
	{
		while (c->av[i])
		{
			do_unsetenv(c, c->av[i]);
			i++;
		}
	}
}
