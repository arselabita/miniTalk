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

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"

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
static void encoding(int ascii_value, int pid)
{
    int j;

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
        j--;
    }
}

int main(int ac, char **av)
{
    pid_t pid;
    pid_t client_pid;
    int i;

	if (ac != 3)
		return (write(2, "ERROR: Write: PID and String!\n", 30), -1);
    if (av[1] == NULL)
        return (write(2, "ERROR: Pass the PID!\n", 24), -1);
    if (!ft_valid_number(av[1]))
		return (write(2, "ERROR: Please input only numbers\n", 33), -1);
    pid = ft_atoi(av[1]);
	i = 0;
    if (av[2] == NULL)
        return (write(2, "ERROR: Pass the String!\n", 24), -1);
    signal(SIGUSR1, msg_received);
	while (av[2][i])
	{
        encoding(av[2][i], pid);
		i++;
	}
    encoding('\0', pid);
    client_pid = getpid();
    return (0);
}
