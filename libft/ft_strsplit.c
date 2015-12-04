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

static int	ft_size(char const *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i])
				i++;
			size++;
			if (s[i] == '\0')
				return (size);
		}
		i++;
	}
	return (size);
}

static void	ft_fuller(char const *s, char c, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
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

static int	ft_wordsize(char const *s, char c, char **tab)
{
	int	i;
	int	j;
	int	wordsize;

	i = 0;
	j = 0;
	while (s[i])
	{
		wordsize = 0;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
			{
				wordsize++;
				i++;
			}
			if (!(tab[j] = (char *)malloc(sizeof(char) * (wordsize + 1))))
				return (0);
			if (s[i] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (!s || !c)
		return (0);
	tab = (char **)malloc(sizeof(char *) * (ft_size((char *)s, c) + 1));
	if (!tab)
		return (0);
	ft_wordsize(s, c, tab);
	ft_fuller(s, c, tab);
	return (tab);
}
