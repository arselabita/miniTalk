/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:13:56 by abita             #+#    #+#             */
/*   Updated: 2025/09/11 12:13:57 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

static int parsing_arguments(char *av)
{
	int i;
    int j;
    int ascii_value;

	i = 0;
    // so basically i will loop through all my str:
    //      1. i convert each character into ascii value
    //      2. then i get the binary of it
	while (av[i])
	{
        j = 7;
        ascii_value = av[i];
        while (j > 0)
        {
		    if (((ascii_value >> j) & 1) == 0)
              kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(100);
            j++;
        }
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 3)
		return (write(2, "ERROR\n", 6), 1);
	if (!parsing_arguments(av[2]))
		return (write(2, "ERROR\n", 6), 1);
	return (0);
}