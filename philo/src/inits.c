/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:08:29 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/21 09:57:54 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	init_info(const int *arr, t_info *info)
{
	info->n_philos = arr[0];
	info->t_die = arr[1];
	info->t_eat = arr[2];
	info->t_sleep = arr[3];
	info->t_start = current_t();
	if (arr[4] >= 0)
		info->n_meals = arr[4];
	else
		info->n_meals = -1;
	info->is_dead = false;
	info->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(info->lock, NULL))
		printf("Mutex init error");
	info->n_full_philos = 0;
}

void
	init_philos(int n_philos, t_philo *ph_arr,
				pthread_mutex_t *forks, t_info *info)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		ph_arr[i].id = i;
		ph_arr[i].have_eaten = 0;
		ph_arr[i].t_meal = 0;
		ph_arr[i].info = info;
		ph_arr[i].forks = forks;
		ph_arr[i].ph_arr = ph_arr;
		i++;
	}
}

void
	create_philos(int arr[], t_philo *ph_arr, pthread_mutex_t *forks)
{
	t_info			*info;

	info = (t_info *) malloc(sizeof(t_info));
	init_info(arr, info);
	init_philos(arr[0], ph_arr, forks, info);
}

pthread_mutex_t
	*create_forks(int n_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(n_forks * sizeof(pthread_mutex_t));
	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			printf("Mutex init error");
		i++;
	}
	return (forks);
}
