/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:24:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/05 13:24:09 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	philo_log(t_info *info, uint64_t t_stamp, int ph_id, int action, bool is_dead)
{
	pthread_mutex_lock(info->lock);
	if (!is_dead)
	{
		if (action == FORK)
			printf("%llu%s %d %s\n", t_stamp, "ms", ph_id, FORK_MSG);
		else if (action == EAT)
			printf("%llu%s %d %s\n", t_stamp, "ms", ph_id, EAT_MSG);
		else if (action == SLEEP)
			printf("%llu%s %d %s\n", t_stamp, "ms", ph_id, SLEEP_MSG);
		else if (action == THINK)
			printf("%llu%s %d %s\n", t_stamp, "ms", ph_id, THINK_MSG);
		else if (action == DIE)
			printf("%llu%s %d %s\n", t_stamp, "ms", ph_id, DIE_MSG);
	}
	pthread_mutex_unlock(info->lock);
}

void
	take_fork(t_philo philo, int fork)
{
	if (fork == LEFT)
	{
		if (!pthread_mutex_lock(&philo.forks[philo.id]))
			philo_log(philo.info, get_t_diff(philo.info->t_start), philo.id + 1, FORK, philo.info->is_dead);
	}
	else
	{
		if (philo.id == 0)
		{
			if (!pthread_mutex_lock(&philo.forks[philo.info->n_philos - 1]))
				philo_log(philo.info, get_t_diff(philo.info->t_start), philo.id + 1, FORK, philo.info->is_dead);
		}
		else
		{
			if (!pthread_mutex_lock(&philo.forks[philo.id - 1]))
				philo_log(philo.info, get_t_diff(philo.info->t_start), philo.id + 1, FORK, philo.info->is_dead);
		}
	}
}

void
	take_forks(t_philo philo)
{
	if (philo.info->n_philos < 2)
	{
		ms_sleep(philo.info->t_sleep);
	//	philo.info->is_dead = true;
		return ;
	}

	if (philo.id % 2)
	{
		take_fork(philo, RIGHT);
		take_fork(philo, LEFT);
	}
	else
	{
		take_fork(philo, LEFT);
		take_fork(philo, RIGHT);
	}
}

void
	drop_forks(t_philo philo)
{
	if (philo.id == 0)
		pthread_mutex_unlock(&philo.forks[philo.info->n_philos - 1]);
	else
		pthread_mutex_unlock(&philo.forks[philo.id - 1]);
	pthread_mutex_unlock(&philo.forks[philo.id]);
}
