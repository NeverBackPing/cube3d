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

//checkmap.c
int	checkmap(char **tab);
int	ft_cins(char *str, char c);
int	ft_slen(char *s);
//handler_fd.c
void	handler_fd(char	*fd);
//handler_input.c
void	handler_argument(int ac);
//ft_get_map.c

#endif
