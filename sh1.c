#include <unistd.h>
#include <stdio.h>
#include <libft.h>

#define SHELL_NAME "mychel"

typedef	struct		s_env
{
	char	**my_env;
	char	**av;
	size_t	ac;
	char	*line;
	char	*path;
}					t_env;

int			id_pos(char **env, char *key);
char		**ft_tab_copy_extand(char **env);
void		ft_tab_free(char **env);
char		**ft_tab_copy(char **env);
char		*new_env_line(char *av1, char *av2);
char		*ft_str_triple_join(const char *s1, const char *s2, const char *s3);
char		*get_env_value(char **env, char *key);

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

void		builtin_env(t_env *c)
{
	const char	error[] = "env: Too many arguments.\n";

	if (c->ac > 1)
		write(1, error, sizeof(error) - 1);
	else
		put_string_tab(c->my_env);
}

char		**set_env_element(char **env, char *key, char *value)
{
	int		i;
	int		j;

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

int			file_exist(char *str)
{
	if (access(str, F_OK) == -1)
		return (0);
	else
		return (1);
}

void		do_cd(t_env *c, char *moveto)
{
	char	**tmp;
	char	*oldtmp;
	char	*tmpgetcwd;

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

void		builtin_cd(t_env *c)
{
	char	*pwd;
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

char		*new_env_line(char *av1, char *av2) // Leaks
{
	char	*file;

	if (av2 == 0)
		file = ft_strjoin(av1, "=");
	else
		file = ft_str_triple_join(av1, "=", av2);
	return (file);
}

void		builtin_setenv(t_env *c)
{
	int		j;
	char	**tmp;

	j = 0;
	const char	error[] = "setenv: Too many arguments.\n";

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
	int		i;

	i = 1;
	const char	error[] = "unsetenv: Too few arguments.\n";

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

void		ft_tab_free(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

char		**get_call_command(char *line)
{
	return (ft_split_whitespaces(line));
}

void		unknown_command(t_env *env)
{
	const char	error[] = SHELL_NAME": command not found: ";

	write(1, error, sizeof(error) - 1);
	write(1, env->av[0], strlen(env->av[0]));
	write(1, "\n", 1);
}

char		*get_env_value(char **env, char *key)
{
	int	i;
	int	key_len;
	
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

int			id_pos(char **env, char *key)
{
	int	i;
	int	key_len;
	
	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, key_len) == 0) && (env[i][key_len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

int			is_executable(char *s)
{
	struct stat truc;

	return((stat(s, &truc) == 0) && (truc.st_mode & S_IXUSR));
}

char		*ft_str_triple_join(const char *s1, const char *s2, const char *s3)
{
	char			*finish_string;
	const size_t	len1 = ft_strlen(s1);
	const size_t	len2 = ft_strlen(s2);
	const size_t	len3 = ft_strlen(s3);

	if (!(finish_string = (char *)malloc(sizeof(char) * (len1 + len2 + len3 + 1))))
		return (NULL);
	ft_memcpy(finish_string, s1, len1);
	ft_memcpy(finish_string + len1, s2, len2);
	ft_memcpy(finish_string + len1 + len2, s3, len3);
	finish_string[len1 + len2 + len3] = '\0';
	return (finish_string);
}

char		*finding_bin(t_env *env)
{
	int	i;
	char	*line;
	char	**bins_tab;
	char	*file;
	char	*tmp;

	i = 0;
	if (!(tmp = getcwd(NULL, 0)))
		return (NULL);
	file = ft_str_triple_join(tmp, "/", env->av[0]);
	free(tmp);
	if (is_executable(file))
		return (file);
	else
		free(file);
	if (is_executable(env->av[0]))
		return(ft_strdup(env->av[0]));
	if (!(line = get_env_value(env->my_env, "PATH")))
		return (NULL);
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

void		exec_bin(t_env *c)
{
	const char	error[] = SHELL_NAME": execution error\n";
	int			pid;
	int			status;

	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0)
	{
		execve(c->path, c->av, c->my_env);
		exit (0);
	}
	else
		write(1, error, sizeof(error) - 1);
	free(c->path);
}

size_t		get_ac(char **av)
{
	int		i;

	i = 0;
	while (av[i])
		i++;
	return (i);
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
		if (c->line && *c->line)
		{
			c->av = get_call_command(c->line);
			if (c->av && c->av[0])
			{
				c->ac = get_ac(c->av);
				if (!ft_strcmp(c->av[0], "env"))
					builtin_env(c);
				else if (!ft_strcmp(c->av[0], "cd"))
					builtin_cd(c);
				else if (!ft_strcmp(c->av[0], "setenv"))
					builtin_setenv(c);
				else if (!ft_strcmp(c->av[0], "unsetenv"))
					builtin_unsetenv(c);
				else if (!ft_strcmp(c->av[0], "exit") || !ft_strcmp(c->av[0], "bye"))
					builtin_exit(c);
				else if ((c->path = finding_bin(c)))
					exec_bin(c);
				else
					unknown_command(c);
			}
			ft_tab_free(c->av);
		}
		free(c->line);
		write(1, "$> ", 3);
	}
	return (0);
}