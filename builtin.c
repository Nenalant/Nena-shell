/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 19:59:12 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 19:59:16 by alanteri         ###   ########.fr       */
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

void		do_cd(t_env *c, char *moveto)
{
	char		**tmp;
	char		*oldtmp;
	char		*tmpgetcwd;

	oldtmp = getcwd(NULL, 0);
	if (chdir(moveto) == -1)
	{
		write(1, "cd: ", 4);
		write(1, moveto, ft_strlen(moveto));
		write(1, ": No such file or directory\n", 28);
		free(oldtmp);
		return ;
	}
	tmp = set_env_element(c->my_env, "OLDPWD", oldtmp);
	ft_tab_free(c->my_env);
	c->my_env = tmp;
	tmpgetcwd = getcwd(NULL, 0);
	tmp = set_env_element(c->my_env, "PWD", tmpgetcwd);
	free(tmpgetcwd);
	ft_tab_free(c->my_env);
	c->my_env = tmp;
	free(oldtmp);
}

char		*get_env_value(char **env, char *key)
{
	int			i;
	int			key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, key_len) == 0) && (env[i][key_len] == '='))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void		builtin_cd(t_env *c)
{
	char		*pwd;
	const char	error[] = "cd: Too many arguments.\n";

	if (c->ac > 2)
		write(1, error, sizeof(error) - 1);
	else if (c->ac == 1)
	{
		if ((pwd = get_env_value(c->my_env, "HOME")))
			do_cd(c, pwd + 5);
	}
	else if (ft_strcmp(c->av[1], "-") == 0)
	{
		if (!(pwd = get_env_value(c->my_env, "OLDPWD")))
			write(1, ": No such file or directory.\n", 29);
		else
			do_cd(c, pwd + 7);
	}
	else
		do_cd(c, c->av[1]);
}

void		builtin_exit(t_env *c)
{
	int		i;
	char	*ptr;

	ptr = c->line;
	while (ptr[0] == ' ' || ptr[0] == '\t')
		ptr++;
	ptr += 4;
	i = ft_atoi(ptr);
	free(c);
	exit(i);
}
