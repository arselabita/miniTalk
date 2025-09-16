/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:08 by abita             #+#    #+#             */
/*   Updated: 2025/09/11 12:14:11 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>
/*
    Message Passing is a method where processes communicate by sending 
    and receiving messages to exchange data.
        1. In this method, one process sends a message and the other process 
            receives it, allowing them to share information.
        2. Message Passing can be achieved through different methods like 
            Sockets, Message Queues or Pipes.
*/

void handler(int signal)
{
    if (signal == 0)
        write(1, "0", 1);
    else
        write(1, "1", 1);
}
int main (int ac, char **av)
{
    pid_t my_pid;

	my_pid = getpid(); // geting the process id
    ft_printf("%d", (int)my_pid);

    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

}