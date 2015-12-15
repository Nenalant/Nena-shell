/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 19:59:49 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 19:59:57 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>

# define SHELL_NAME "mychel"
# define PROMPT "$> "

typedef	struct		s_env
{
	char			**my_env;
	char			**av;
	size_t			ac;
	char			*line;
	char			*path;
}					t_env;

void				builtin_echo(t_env *c);
char				try_cd(char *moveto, char *oldtmp);
void				do_cd(t_env *c, char *moveto);
void				builtin_cd(t_env *c);
void				builtin_exit(t_env *c);

char				**set_env_element(char **env, char *key, char *value);
void				builtin_env(t_env *c);
void				builtin_setenv(t_env *c);
void				do_unsetenv(t_env *c, char *key);
void				builtin_unsetenv(t_env *c);

void				exec_bin(t_env *c);
size_t				get_ac(char **av);
void				put_string_tab(char **str);
char				**ft_tab_copy(char **env);
char				**ft_tab_copy_extand(char **env);

char				**get_call_command(char *line);
char				*new_env_line(char *av1, char *av2);
int					id_pos(char **env, char *key);
int					is_executable(char *s);
char				*ft_str_triple_join(const char *s1, const char *s2,
										const char *s3);

int					file_exist(char *str);
void				unknown_command(t_env *env);
char				*get_env_value(char **env, char *key);
char				do_builtin(t_env *c);

void				builtin_pwd(t_env *c);
void				ft_tab_free(char **env);
char				*triple_join(t_env *env, char *file, char *line);
char				*finding_bin(t_env *env);
void				builtin_export(t_env *c);

void				builtin_builtin(t_env *c);
void				launch_command(t_env *c);
void				do_unset(t_env *c, char *key);
void				builtin_unset(t_env *c);

void				shlvl(t_env *c);
void				do_sigint(int num);

#endif
