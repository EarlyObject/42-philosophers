/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:24:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/10 13:43:49 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	philo_log(t_info *info, t_philo *philo, int ph_id, int action)
{
	uint64_t	t_stamp;

	pthread_mutex_lock(philo->info->lock);
	t_stamp = get_t_diff(info->t_start);
	if (!info->is_dead)
	{
		if (action == FORK)
			printf("%llu %d %s\n", t_stamp, ph_id, FORK_MSG);
		else if (action == EAT)
			printf("%llu %d %s\n", t_stamp, ph_id, EAT_MSG);
		else if (action == SLEEP)
			printf("%llu %d %s\n", t_stamp, ph_id, SLEEP_MSG);
		else if (action == THINK)
			printf("%llu %d %s\n", t_stamp, ph_id, THINK_MSG);
	}
	pthread_mutex_unlock(philo->info->lock);
}

void
	philo_log_death(int ph_id, t_info *info)
{
	uint64_t	t_stamp;

	pthread_mutex_lock(info->lock);
	t_stamp = get_t_diff(info->t_start);
	printf("%llu %d %s\n", t_stamp, ph_id, DIE_MSG);
	pthread_mutex_unlock(info->lock);
}

void
	take_fork(t_philo ph, int fork)
{
	if (fork == LEFT)
	{
		if (!pthread_mutex_lock(&ph.forks[ph.id]))
			philo_log_fork(ph.info, ph.id + 1);
	}
	else
	{
		if (ph.id == 0)
		{
			if (!pthread_mutex_lock(&ph.forks[ph.info->n_philos - 1]))
				philo_log_fork(ph.info, ph.id + 1);
		}
		else
		{
			if (!pthread_mutex_lock(&ph.forks[ph.id - 1]))
				philo_log_fork(ph.info, ph.id + 1);
		}
	}
}

void
	take_forks(t_philo philo)
{
	if (philo.info->n_philos < 2)
	{
		take_fork(philo, LEFT);
		ms_sleep(philo.info->t_die + 1, &philo);
		life_indicator(philo.info, &philo);
		pthread_mutex_unlock(&philo.forks[philo.id]);
		return ;
	}
	take_fork(philo, LEFT);
	take_fork(philo, RIGHT);
}

void
	drop_forks(t_philo philo)
{
	philo_log(philo.info, &philo, philo.id + 1, SLEEP);
	pthread_mutex_unlock(&philo.forks[philo.id]);
	if (philo.id == 0)
		pthread_mutex_unlock(&philo.forks[philo.info->n_philos - 1]);
	else
		pthread_mutex_unlock(&philo.forks[philo.id - 1]);
}
