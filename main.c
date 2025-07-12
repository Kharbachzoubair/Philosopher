/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:52:39 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/12 16:42:22 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_digit_str(const char *str)
{
	int i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
		else
			i++;
	return (1);
}

int safe_atoi(const char *str, int *result)
{
	long num = 0;
	int i = 0;
	if (!is_digit_str(str))
		return (0);
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	*result = (int)num;
	return (1);
}

long long get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long long time, t_data *data)
{
	long long start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(100);
	}
}

int parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!safe_atoi(argv[1], &data->nb_philos) || data->nb_philos <= 0)
		return (0);
	if (!safe_atoi(argv[2], &data->time_to_die) || data->time_to_die <= 0)
		return (0);
	if (!safe_atoi(argv[3], &data->time_to_eat) || data->time_to_eat <= 0)
		return (0);
	if (!safe_atoi(argv[4], &data->time_to_sleep) || data->time_to_sleep <= 0)
		return (0);
	if (argc == 6)
	{
		if (!safe_atoi(argv[5], &data->must_eat) || data->must_eat <= 0)
			return (0);
		data->has_optional_arg = 1;
	}
	else
		data->has_optional_arg = 0;
	return (1);
}

void print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lld %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->data->nb_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		take_forks(philo);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->last_meal = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_usleep(philo->data->time_to_eat, philo->data);
		drop_forks(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void one_philo(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	print_status(philo, "died");
	philo->data->someone_died = 1;
}

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			long long time_since_meal = get_time() - data->philos[i].last_meal;
			if (!data->someone_died && time_since_meal > data->time_to_die)
			{
				data->someone_died = 1;
				pthread_mutex_lock(&data->print_mutex);
				printf("%lld %d died\n", get_time() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
		}
		usleep(1000);
	}
}

int init_simulation(t_data *data)
{
	int i;

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
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data))
		return (1);
	return (0);
}

void cleanup(t_data *data)
{
	int i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor_thread, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	free(data->forks);
	free(data->philos);
}

int main(int argc, char **argv)
{
	t_data data;

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
