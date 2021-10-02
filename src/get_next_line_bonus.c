/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe <rrajaobe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:07:10 by rrajaobe          #+#    #+#             */
/*   Updated: 2021/10/02 12:38:20 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line_bonus.h"

/*
**	BONUS PART
**	Basically the same approach used for the mandatory part (get_next_line.c) with minimal changes.
**	In order to work with as many file descriptors as we want, we are able to do this if we are not exceding the limit value of 10240,
**	that is the predefined macro limit for open files per process (handled @line 75/78). 
**	Regarding the use of static variable, this case was already handled int he mandatory part. 
*/

static char	*rest_check(char **rest)
{
	char	*current_line;
	char	*temp;
	int		new_line_position;

	current_line = NULL;
	new_line_position = ft_my_strchr(*rest, '\n');
	if ((new_line_position >= 0))
	{
		temp = ft_strdup(&rest [new_line_position + 1]);
		current_line = ft_substr(*rest, 0, new_line_position + 1);
		free(*rest);
		*rest = ft_strdup(temp);
		free(temp);
		return (current_line);
	}
	if (*rest[0] != '\0')
		current_line = ft_strdup(*rest);
	free(*rest);
	*rest = NULL;
	return (current_line);
}

static int	buffer_check(int fd, char *buf, char **rest, int b)
{
	char	*temp;

	while (b > 0)
	{
		buf[b] = '\0';
		if (!(*rest))
			*rest = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(*rest, buf);
			free(*rest);
			*rest = ft_strdup(temp);
			free(temp);
		}
		if (ft_my_strchr(buf, '\n') >= 0)
			break ;
		else
			b = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	buf = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*rest[10240];
	int			b;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (0);
	buf = NULL;
	buf = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	b = read(fd, buf, BUFFER_SIZE);
	if (b <= 0)
	{
		if (rest[fd] == 0)
		{
			free(buf);
			buf = NULL;
			return (0);
		}
	}
	buffer_check(fd, buf, &rest[fd], b);
	return (rest_check(&rest[fd]));
}
