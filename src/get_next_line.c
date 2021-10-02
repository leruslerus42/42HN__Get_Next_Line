/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe <rrajaobe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 08:35:34 by rrajaobe          #+#    #+#             */
/*   Updated: 2021/10/02 12:37:36 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/*
**		PROJECT NOTES
**	-	I have used the variable "temp" to avoid any memory leaks. 
**	-	Of course in order to have a memory leaks-free programm
**		we free immediatly after that we do not need the value of the variables anymore. 
*/

/*
**		CHECKING THE REST
**	1)	I check if in rest is present a new line (line 27).
**	2)	
**		2.1)	If yes, I copy the string after the new line in a temporany variable, and return the intial substring between 
**			index 0 and the index of the new line.
**			
**		2.2)	If not, we are currently on the last line of our file.
**			I check if we are at the End of File (line 45). If not I copy and return the last string, otherwise I return NULL.
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
		temp = ft_strdup(&rest[0][new_line_position + 1]);
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


/*
**		CHECKING THE BUFFER
**	1)	As long as the amount of bytes is positive, so it means we are still not at the End of File
**	2)	If is the first line readed, I will copy the buffer in the static variable rest (line 52), otherwise I append the 
**		rest of the string, due to a limitation imposed by BUFFER_SIZE, that was not readed yet and that is now memorized in the buffer
**		to our static rest.
**	3)	If we find a new line (line59), we will exit the loop. 
**		Otherwise we will continue reading the line, memorizing the readed bytes in buffer and so on.
*/

static char	*buffer_check(int fd, char *buf, char **rest, int b)
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
			b = read (fd, buf, BUFFER_SIZE);
	}
	free (buf);
	buf = NULL;
	return (rest_check(rest));
}


/*
**		CONTROLLER FUNCTION
**	1)	Error Management.
**	2)	Allocating memory for the buffer.
**	3)	Reading the file memorized in the file descriptor and writing it in the buffer with lenght BUFFER_SIZE, 
**		and having the variable b representing the readed bytes.
*/

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*rest;
	int			b;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = NULL;
	buf = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	b = read(fd, buf, BUFFER_SIZE);
	if (b <= 0)
	{
		if (rest == 0)
		{
			free(buf);
			buf = NULL;
			return (0);
		}
	}
	return (buffer_check(fd, buf, &rest, b));
}
