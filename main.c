/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:52:39 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/19 10:19:34 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_struct(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].meals = 0;
	data->philos[i].data = data;
	data->philos[i].left_fork = &data->forks[i];
	data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
	data->philos[i].last_meal = get_time();
}

int	init_simulation(t_data *data)
{
	int		i;

	data->someone_died = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->forks || !data->philos)
		return (1);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->nb_philos)
	{
		init_philo_struct(data, i);
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data))
	{
		printf("Error: Invalid arguments.\n");
		return (1);
	}
	if (init_simulation(&data))
		return (1);
	cleanup(&data);
	return (0);
}
