/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:49:27 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/04 09:49:28 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	launch_threads(t_philo *ph_arr, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&ph_arr[i].pthread, NULL, &philo_life, &ph_arr[i]);
		i++;
	}
}

void
	join_threads(t_philo *ph_arr, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(ph_arr[i].pthread, NULL);
		i++;
	}
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

void
	check_if_all_full(t_info *info)
{
	pthread_mutex_lock(info->lock);
	if (info->n_full_philos == info->n_philos)
	{
		if (!info->is_dead)
		{
			printf("All philosophers have completed their meal\n");
			info->is_dead = true;
		}
	}
	pthread_mutex_unlock(info->lock);
}
