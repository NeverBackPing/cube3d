/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:23:07 by gtraiman          #+#    #+#             */
/*   Updated: 2025/02/27 16:02:13 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checkmap.h>

int	ft_slen(char *s)
{
	int	i;

	i = 0;
    if(!s)
        return(0);
	while (s[i])
		i++;
	return (i);
}

int	ft_cins(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int checkmap(char **tab)
{
    int i;
    int j;
    int cpt;

    i = 0;
    j = 0;
    cpt = 0;
    while(tab[i][j])
    {
        if(ft_cins("1 ",tab[i][j]) != 1)
            return(1);
        j++;
    }
    i++;
    while(tab[i])
    {
        if(tab[i][0] == '0')
            return(1);
        j = 1;
        while(tab[i][j])
        {
            if(ft_cins("0NEWS",tab[i][j]) == 1)
            {
                if(tab[i][j] != '0')
                    cpt++;
                if((ft_slen(tab[i - 1]) < j || ft_slen(tab[i + 1]) < j))
                    return(1);
                if(ft_cins("0NEWS1",tab[i - 1][j]) == 0 || ft_cins("0NEWS1",tab[i + 1][j]) == 0)
                    return(1);
                if((j != 0 && ft_cins("0NEWS1",tab[i][j - 1]) == 0) || ft_cins("0NEWS1",tab[i][j + 1]) == 0)
                    return(1);
            }
            j++;
        }
        i++;
    }
    if(cpt != 1)
        return(1);
    return(0);
}

// int main(int ac, char **av)
// {
//     if(ac < 2)
//         return(printf("Error"));
//     char *tab[] =
//     {
//         "11111111111111",
//         "10010000001",
//         "10100111111",
//         "1100N1",
//         "111111",
//         NULL
//     };
//     printf("%d",checkmap(tab));
// }