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

//#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

/*
    Message Passing is a method where processes communicate by sending 
    and receiving messages to exchange data.
        1. In this method, one process sends a message and the other process 
            receives it, allowing them to share information.
        2. Message Passing can be achieved through different methods like 
            Sockets, Message Queues or Pipes.
*/


void handler(int sig)
{
    static unsigned char bits = 0;
    static int bit_position = 0;

    if (sig == SIGUSR1)
        bits = (bits << 1) | 0;
    else
        bits = (bits << 1) | 1;
    bit_position++;
    if (bit_position == 8)
    {
        if (bits != '\0')
            write(1, &bits, 1);
        else
            write(1, "\n", 1);
        bits = 0;
        bit_position = 0;        
    }
}

int main()
{
    pid_t pid;

    pid = getpid();
    printf("%d\n", (int)pid);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    while (1)
        pause();
    return (0);
}
