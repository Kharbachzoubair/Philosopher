/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:48:23 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/06 13:12:08 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_data {
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	has_optional_arg;
}	t_data;

// args.c
int	parse_args(int argc, char **argv, t_data *data);

// utils.c
int	safe_atoi(const char *str, int *result);
int	is_digit_str(const char *str);

#endif
