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
typedef struct s_bits
{
    unsigned char bits;
    int bit_position;
} t_bits;

static t_bits bits = {0, 0};

void handler1(int sig)
{
    bits.bits = (bits.bits << 1) | 0;
    bits.bit_position++;
    if (bits.bit_position == 8)
    {
        if (bits.bits != '\0')
            write(1, &bits.bits, 1);
        else
            write(1, "\n", 1);
        bits.bits = 0;
        bits.bit_position = 0;        
    }
}

void handler2(int sig)
{
    bits.bits = (bits.bits << 1) | 1;
    bits.bit_position++;
    if (bits.bit_position == 8)
    {
        if (bits.bits != '\0')
            write(1, &bits.bits, 1);
        else
            write(1, "\n", 1);
        bits.bits = 0;
        bits.bit_position = 0;        
    }
}

int main()
{
    pid_t pid;

    pid = getpid();
    printf("%d\n", (int)pid);
    signal(SIGUSR1, handler1);
    signal(SIGUSR2, handler2);
    while (1)
        pause();
    return (0);
}
