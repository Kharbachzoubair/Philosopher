/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:52:39 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/06 13:11:16 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data))
	{
		printf("Error: Invalid arguments.\n");
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}

	// Debug print (remove later)
	printf("Philosophers: %d\n", data.nb_philos);
	printf("Time to die: %d\n", data.time_to_die);
	printf("Time to eat: %d\n", data.time_to_eat);
	printf("Time to sleep: %d\n", data.time_to_sleep);
	if (data.has_optional_arg)
		printf("Must eat: %d times\n", data.must_eat);
	else
		printf("No meal limit.\n");

	// Continue to init forks, create threads, etc.

	return (0);
}
