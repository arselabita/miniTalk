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

int main()
{
	long id;

	id = getpid(); // geting the process id
	printf("id: %ld\n", id);
	return (0);
}