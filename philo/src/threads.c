/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:49:27 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/21 09:58:03 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	launch_threads(t_philo *ph_arr, int n_philos)
{
	int	i;

	i = 1;
	while (i < n_philos)
	{
		pthread_create(&ph_arr[i].pthread, NULL, &philo_life, &ph_arr[i]);
		i += 2;
		usleep(210 - ph_arr->info->n_philos);
	}
	i = 0;
	while (i < n_philos)
	{
		pthread_create(&ph_arr[i].pthread, NULL, &philo_life, &ph_arr[i]);
		i += 2;
		usleep(210 - ph_arr->info->n_philos);
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

void
	check_if_all_full(t_info *info)
{
	if (info->n_full_philos == info->n_philos)
	{
		pthread_mutex_lock(info->lock);
		if (!info->is_dead)
		{
			info->is_dead = true;
		}
		pthread_mutex_unlock(info->lock);
	}
}
