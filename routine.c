/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:20:17 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/20 17:29:58 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

static void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	drop_forks(philo);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
	print_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!stop_simulation(philo))
	{
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (NULL);
}

void	one_philo(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_lock(&philo->data->death_mutex);
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->data->death_mutex);
	exit(0);
}
