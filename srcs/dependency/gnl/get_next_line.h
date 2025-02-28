/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:54:26 by sjossain          #+#    #+#             */
/*   Updated: 2024/06/04 18:18:18 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <../includes/main.h>


char	*get_next_line(int fd);
int		is_end(char *buffer);
char	*clear_s(char *stash);
void	update_b(char *buffer);
int		read_fd(char *buffer, int read_buffer, char **stash, int fd);
size_t	count_line(char *stash);

#endif
