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

void handler1(int sig)
{
    unsigned int add_bits;
    unsigned int bit_position;

    add_bits = 0;
    if (sig == SIGUSR1)
        add_bits |= 1;
    bit_position++;
    if (bit_position == 8)

    (void)sig;
    write(1, "0", 1);
}
void handler2(int sig)
{
    (void)sig;
    write(1, "0", 1);
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



// void handler2(int sig)
// {
//     int count;
//     int i;
//     char save_the_bit;

//     count = 0;
//     if (sig == SIGUSR1)
//         save_the_bit += 1;
//     count++;
//     if (count == 8)


// }
