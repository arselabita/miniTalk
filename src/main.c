/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:21 by abita             #+#    #+#             */
/*   Updated: 2025/09/11 12:14:24 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

int parsing_arguments(char **av)
{
	int i;
	int j;

	i = 0;
	while (av[1][i])
	{
		write(1, av[1][i], 1);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	long id;

	if (ac != 2)
		return (write(2, "ERROR\n", 6), 1);
	if (!parsing_arguments(av))
		return (write(2, "ERROR\n", 6), 1);

	id = getpid(); // geting the process id
	printf("id: %ld\n", id);

	client(id, av);
	return (0);
}