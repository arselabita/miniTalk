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

// #include "minitalk.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

static int	ft_valid_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{
    pid_t pid;
    int i;
    int j;
    int ascii_value;

	if (ac != 3)
		return (write(2, "ERROR\n", 6), -1);
    if (av[1] == NULL)
        return (write(2, "ERROR\n", 6), -1);
    if (!ft_valid_number(av[1]))
		return (write(2, "ERROR\n", 6), -1);
    pid = atoi(av[1]);
	i = 0;
	while (av[2][i])
	{
        j = 7;
        ascii_value = av[2][i];
        while (j >= 0)
        {
		    if ((ascii_value >> j) & 1)
            {
                if (kill(pid, SIGUSR2) == -1)
                    exit(EXIT_FAILURE);
            }
            else
            {
                if (kill(pid, SIGUSR1) == -1)
                    exit(EXIT_FAILURE);
            }
            usleep(100);
            j--;
        }
		i++;
	}    
    ascii_value = '\0';
    j = 7;
    while (j >= 0)
    {   
	    if ((ascii_value >> j) & 1)
        {
            if (kill(pid, SIGUSR2) == -1)    
                exit(EXIT_FAILURE);
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1)
                exit(EXIT_FAILURE);
        }
        usleep(100);
        j--;
    }
	return (0);
}
