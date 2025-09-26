/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:59:03 by abita             #+#    #+#             */
/*   Updated: 2025/09/19 20:59:04 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>
#include "libft.h"

volatile sig_atomic_t	g_perm_to_send_next_bit;

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

static int	encoding(int ascii_value, int pid)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		while (g_perm_to_send_next_bit == false)
			;
		g_perm_to_send_next_bit = false;
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
//		usleep(100);
		j--;
	}
	return (0);
}

void	give_perm_for_sending_next_bit(int sig)
{
// #include <stdio.h>
// static int i = 0; i++; printf("---------\ni: %d\n", i);
	if (sig == SIGUSR1)
	{
		g_perm_to_send_next_bit = true;
//		write(1, "signal received... its hereeee!\n", 32);
	}
	else if (sig == SIGUSR2)
	{
		g_perm_to_send_next_bit = true;
//		write(1, "signal SIGUSR2 received --------------------!\n", 47);
	}
}

static int	parsing(int ac, char **av)
{
	pid_t	pid;
	int		i;

	if (ac != 3)
		return (write(2, "ERROR: Write: PID and String!\n", 30), 1);
	if (av[1] == NULL)
		return (write(2, "ERROR: Pass the PID!\n", 24), -1);
	if (!ft_valid_number(av[1]))
		return (write(2, "ERROR: Please input only numbers\n", 33), 1);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (write(2, "ERROR: U trying to kill it heheh 😑", 37), 1);
	if (av[2] == NULL)
		return (write(2, "ERROR: Pass the String!\n", 24), 1);
g_perm_to_send_next_bit = true;
	i = 0;
	while (av[2][i])
	{
		if (encoding(av[2][i], pid) == -1)
			return (write(2, "Error: Kill failed\n", 19), 1);
		i++;
	}
	if (encoding('\0', pid) == -1)
		return (write(2, "Error: Kill failed\n", 19), 1);
	return (0);
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, give_perm_for_sending_next_bit);
	signal(SIGUSR2, give_perm_for_sending_next_bit);
	if (parsing(ac, av) == 1)
		return (write(2, "Error!\n", 7), 1);
	return (0);
}
