/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:13:56 by abita             #+#    #+#             */
/*   Updated: 2025/09/26 20:58:50 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <signal.h>
#include <limits.h>
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
		j--;
	}
	return (0);
}

void	give_perm_for_sending_next_bit(int sig, siginfo_t *info, void *ucontext)
{
	(void) info;
	(void) ucontext;
	if (sig == SIGUSR1)
	{
		write(1, "Server confirmed, that the message was received!\n", 50);
		g_perm_to_send_next_bit = true;
	}
	else if (sig == SIGUSR2)
	{
		g_perm_to_send_next_bit = true;
	}
}

static int	parsing(char **av)
{
	long long	tmp_pid;
	pid_t		pid;
	int			i;

	tmp_pid = ft_atol(av[1]);
	if (tmp_pid <= 0 || tmp_pid > INT_MAX)
		return (write(2, "ERROR: U trying to kill it heheh 😑 \n", 40), 1);
	pid = (pid_t)tmp_pid;
	if (kill(pid, 0) == -1)
		return (write(2, "ERROR: PID does not exist!\n", 28), 1);
	if (av[2] == NULL)
		return (write(2, "ERROR: Pass a non-empty String!\n", 33), 1);
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
	sleep (5);
	return (0);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_sigaction = &give_perm_for_sending_next_bit;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error: sigaction\n", 17), -1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "Error: sigaction\n", 17), -1);
	if (ac != 3)
		return (write(2, "ERROR: Be careful!\n", 20), 1);
	if (av[1] == NULL)
		return (write(2, "ERROR: Pass the PID!\n", 24), -1);
	if (!ft_valid_number(av[1]))
		return (write(2, "ERROR: Please input only numbers\n", 33), 1);
	if (parsing(av) == 1)
		return (write(2, "Error!\n", 7), 1);
	return (0);
}
