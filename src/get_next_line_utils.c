/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe <rrajaobe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:52:15 by rrajaobe          #+#    #+#             */
/*   Updated: 2021/10/02 12:37:54 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/*
**	HELP FUNCTIONS
*/

/*
**Function that returns the lenght of a string.
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i += 1;
	return (i);
}


/*
**	Function that returns a copy of the original string.
*/

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*tab;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == 0)
		return (0);
	while (i < len)
	{
		tab [i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}


/*
**	Function that returns a new string, that is the concatenation of the two originals strings gave as parameters.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	j = 0;
	tab = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tab == 0)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	tab[i] = '\0';
	return (tab);
}


/*
**	Function that returns a substring of the original string, starting atthe index "start" and of maximal lenght "len".
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	size_t			i;
	unsigned int	len2;

	i = 0;
	len2 = ft_strlen(s);
	if (len2 <= start)
	{
		tab = malloc(1);
		tab[0] = '\0';
		return (tab);
	}
	else if (len2 < start + len)
		len = len2 - start;
	tab = malloc(len + 1);
	if (tab == 0)
		return (0);
	while ((i < len) && s[start])
	{
		tab[i] = s[start];
		start++;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}


/*
**	Function that check if a unique charachter is present in the string gave as input.
*/

int	ft_my_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	i = -99;
	return (i);
}
