/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 12:25:53 by alanteri          #+#    #+#             */
/*   Updated: 2014/12/12 19:09:58 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (s)
	{
		new = (char *)malloc(sizeof(char) * (len + 1));
		if (new == NULL)
			return (NULL);
		ft_bzero(new, len);
		while (i < len && s[start])
		{
			new[i] = (char)s[start];
			start++;
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
