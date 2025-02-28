/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:11:52 by sjossain          #+#    #+#             */
/*   Updated: 2024/06/04 18:23:07 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

void	update_b(char *buffer)
{
	size_t	i;
	size_t	len;
	size_t	length;
	char	*head;

	i = 0;
	length = 0;
	len = count_line(buffer);
	head = buffer;
	while (head[i++] != '\0')
		length++;
	ft_strlcpy(head, &buffer[len], length);
}

int	read_fd(char *buffer, int read_buffer, char **stash, int fd)
{
	size_t	i;

	i = 1;
	if (*stash && BUFFER_SIZE != read_buffer)
	{
		while (i)
		{
			i = 0;
			if ((int)count_line(*stash) >= read_buffer)
				break ;
			free(*stash);
			*stash = ft_strdup(buffer);
		}
	}
	read_buffer = read(fd, buffer, BUFFER_SIZE);
	return (read_buffer);
}
