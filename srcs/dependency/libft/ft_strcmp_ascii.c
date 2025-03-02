/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:08:46 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/28 16:55:12 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_ascii(const char *s1, int ascii)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' )
	{
		if ((unsigned char)s1[i] != ascii)
			return ((unsigned char)(s1[i]) - (unsigned char)ascii);
		i++;
	}
	return (0);
}
