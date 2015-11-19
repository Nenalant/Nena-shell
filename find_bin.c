/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 21:29:12 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 21:29:13 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_tab_free(char **env)
{
	int			i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

char		*triple_join(t_env *env, char *file, char *line)
{
	char	**bins_tab;
	int		i;

	i = 0;
	bins_tab = ft_strsplit(line + 5, ':');
	while (bins_tab[i])
	{
		file = ft_str_triple_join(bins_tab[i], "/", env->av[0]);
		if (is_executable(file))
		{
			ft_tab_free(bins_tab);
			return (file);
		}
		free(file);
		i++;
	}
	ft_tab_free(bins_tab);
	return (NULL);
}

char		*finding_bin(t_env *env)
{
	char	*line;
	char	*file;
	char	*tmp;

	if (!(tmp = getcwd(NULL, 0)))
		return (NULL);
	file = ft_str_triple_join(tmp, "/", env->av[0]);
	free(tmp);
	if (is_executable(file))
		return (file);
	else
		free(file);
	if (is_executable(env->av[0]))
		return (ft_strdup(env->av[0]));
	if (!(line = get_env_value(env->my_env, "PATH")))
		return (NULL);
	return (triple_join(env, file, line));
}

void		builtin_export(t_env *c)
{
	int			i;
	char		**tmp;
	char		*ptr;

	i = 1;
	while (c->av[i])
	{
		if (!(ptr = ft_strchr(c->av[i], '=')))
			tmp = set_env_element(c->my_env, c->av[i], "");
		else
		{
			*ptr = '\0';
			tmp = set_env_element(c->my_env, c->av[i], ptr + 1);
			*ptr = '=';
		}
		ft_tab_free(c->my_env);
		c->my_env = tmp;
		i++;
	}
}
