/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 19:59:12 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 19:59:16 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define UNKNOWN_COMMAND_ERROR SHELL_NAME": command not found: "

int			file_exist(char *str)
{
	if (access(str, F_OK) == -1)
		return (0);
	else
		return (1);
}

void		unknown_command(t_env *env)
{
	const char	error[] = UNKNOWN_COMMAND_ERROR;

	write(1, error, sizeof(error) - 1);
	write(1, env->av[0], ft_strlen(env->av[0]));
	write(1, "\n", 1);
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

char		do_builtin(t_env *c)
{
	c->ac = get_ac(c->av);
	if (!ft_strcmp(c->av[0], "builtin"))
		builtin_builtin(c);
	else if (!ft_strcmp(c->av[0], "env"))
		builtin_env(c);
	else if (!ft_strcmp(c->av[0], "cd"))
		builtin_cd(c);
	else if (!ft_strcmp(c->av[0], "setenv"))
		builtin_setenv(c);
	else if (!ft_strcmp(c->av[0], "export"))
		builtin_export(c);
	else if (!ft_strcmp(c->av[0], "unset"))
		builtin_unset(c);
	else if (!ft_strcmp(c->av[0], "unsetenv"))
		builtin_unsetenv(c);
	else if (!ft_strcmp(c->av[0], "exit") || !ft_strcmp(c->av[0], "bye"))
		builtin_exit(c);
	else if (!ft_strcmp(c->av[0], "echo"))
		builtin_echo(c);
	else if (!ft_strcmp(c->av[0], "pwd"))
		builtin_pwd(c);
	else
		return (0);
	return (1);
}

int			main(int ac, char **av, char **env)
{
	t_env	*c;

	(void)ac;
	(void)av;
	if (!(c = (t_env *)malloc(sizeof(t_env))))
		return (-1);
	c->my_env = ft_tab_copy(env);
	write(1, "$> ", 3);
	while (get_next_line(0, &c->line) == 1)
	{
		launch_command(c);
		free(c->line);
		write(1, "$> ", 3);
	}
	return (0);
}
