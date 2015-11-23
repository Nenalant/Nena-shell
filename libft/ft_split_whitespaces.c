/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 12:35:35 by alanteri          #+#    #+#             */
/*   Updated: 2015/04/01 15:26:23 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char const *s)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
		{
			while (s[i] != ' ' && s[i] != '\t' && s[i])
				i++;
			size++;
			if (s[i] == '\0')
				return (size);
		}
		i++;
	}
	return (size);
}

static void	ft_fuller(char const *s, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		if (s[i] != ' ' && s[i] != '\t' && s[i])
		{
			while (s[i] != ' ' && s[i] != '\t' && s[i])
			{
				tab[j][k] = s[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
		if (s[i])
			i++;
	}
	tab[j] = NULL;
}

static int	ft_wordsize(char const *s, char **tab)
{
	int	i;
	int	j;
	int	wordsize;

	i = 0;
	j = 0;
	while (s[i])
	{
		wordsize = 0;
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
		{
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
			{
				wordsize++;
				i++;
			}
			if (!tab[j] = (char *)malloc(sizeof(char) * (wordsize + 1)))
				return (0);
			if (s[i] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (1);
}

char		**ft_split_whitespaces(char const *s)
{
	char	**tab;

	if (!s)
		return (0);
	tab = (char **)malloc(sizeof(char *) * (ft_size((char *)s) + 1));
	if (!tab)
		return (0);
	ft_wordsize(s, tab);
	ft_fuller(s, tab);
	return (tab);
}
