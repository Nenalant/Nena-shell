/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anex2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 20:58:37 by alanteri          #+#    #+#             */
/*   Updated: 2015/11/18 20:58:38 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_call_command(char *line)
{
	return (ft_split_whitespaces(line));
}

char		*new_env_line(char *av1, char *av2)
{
	char	*file;

	if (av2 == 0)
		file = ft_strjoin(av1, "=");
	else
		file = ft_str_triple_join(av1, "=", av2);
	return (file);
}

int			id_pos(char **env, char *key)
{
	int		i;
	int		key_len;

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

	return ((stat(s, &truc) == 0) && (truc.st_mode & S_IXUSR));
}

char		*ft_str_triple_join(const char *s1, const char *s2, const char *s3)
{
	char			*finish_string;
	const size_t	len1 = ft_strlen(s1);
	const size_t	len2 = ft_strlen(s2);
	const size_t	len3 = ft_strlen(s3);

	if (!(finish_string = (char *)malloc(sizeof(char) *
		(len1 + len2 + len3 + 1))))
		return (NULL);
	ft_memcpy(finish_string, s1, len1);
	ft_memcpy(finish_string + len1, s2, len2);
	ft_memcpy(finish_string + len1 + len2, s3, len3);
	finish_string[len1 + len2 + len3] = '\0';
	return (finish_string);
}
