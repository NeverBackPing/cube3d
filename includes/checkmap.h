/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:20:35 by gtraiman          #+#    #+#             */
/*   Updated: 2025/02/26 16:23:05 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKMAP_H
# define CHECKMAP_H

# include "main.h"

# define GRAPH_CHECK 6

// checkmap.c
int		checkmap(char **tab);
int		ft_cins(char *str, char c);
// handler_input.c
void	handler_argument(int ac);
// graph_utils.c
int		find_first_word_end_index(const char *line);
// get_rgb.c
int		skip_sep(char *line, int i);
int		skip_spaces(char *line, int i);
#endif
