/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_mngmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:43:07 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/21 09:58:05 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

uint64_t
	current_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + (tv.tv_usec / 1000));
}

uint64_t
	get_t_diff(uint64_t start)
{
	uint64_t		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
	return (time - start);
}

void
	life_indicator(t_info *info, t_philo *p)
{
	uint64_t	t_from_start;
	t_philo		philo;
	int			i;

	t_from_start = get_t_diff(info->t_start);
	i = 0;
	while (i < info->n_philos)
	{
		philo = p->ph_arr[i];
		if (t_from_start - philo.t_meal > info->t_die)
		{
			if (!philo.info->is_dead)
			{
				philo.info->is_dead = true;
				philo_log_death(philo.id + 1, info);
				return ;
			}
		}
		i++;
	}
}

void
	ms_sleep(uint64_t t_sleep, t_philo *philo)
{
	uint64_t		t_limit;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	t_limit = ((tv.tv_sec * (uint64_t)1000)
			   + (tv.tv_usec / 1000)) + t_sleep;
	while (true)
	{
		life_indicator(philo->info, philo);
		usleep(philo->info->n_philos);
		gettimeofday(&tv, NULL);
		if (((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000)) >= t_limit)
			break ;
	}
}

void
	philo_log_fork(t_info *info, int ph_id)
{
	uint64_t	t_stamp;

	t_stamp = get_t_diff(info->t_start);
	if (!info->is_dead)
		printf("%llu %d %s\n", t_stamp, ph_id, FORK_MSG);
}
