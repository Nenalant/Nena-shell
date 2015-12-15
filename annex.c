/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 20:14:24 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 20:14:26 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define FORK_FAIL SHELL_NAME": fork failed: resource temporarily unavailable\n"
#define BIN_ERROR SHELL_NAME": exec format error: "

void		exec_bin(t_env *c)
{
	int			pid;
	int			status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(c->path, c->av, c->my_env);
		write(1, BIN_ERROR, sizeof(BIN_ERROR) - 1);
		write(1, c->av[0], ft_strlen(c->av[0]));
		write(1, "\n", 1);
		exit(0);
	}
	else
		write(1, FORK_FAIL, sizeof(FORK_FAIL) - 1);
	free(c->path);
	signal(SIGINT, &do_sigint);
}

size_t		get_ac(char **av)
{
	int		i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void		put_string_tab(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		write(1, "\n", 1);
		i++;
	}
}

char		**ft_tab_copy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	if (!(new_env = (char**)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char		**ft_tab_copy_extand(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	if (!(new_env = (char**)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	new_env[i + 1] = NULL;
	return (new_env);
}
