/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:14:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/10 13:43:50 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	*life_checker(void *p_philo)
{
	t_philo		*ph;

	ph = (t_philo *)p_philo;
	while (true)
	{
		if ((int)get_t_diff(ph->t_meal) >= ph->info->t_die)
		{
			if (!pthread_mutex_lock(ph->info->lock))
			{
				if (!(ph->info->is_dead))
				{
					philo_log_death(get_t_diff(ph->info->t_start), ph->id + 1);
					ph->info->is_dead = true;
				}
				pthread_mutex_unlock(ph->info->lock);
				return (ph);
			}
		}
		if (ph->info->is_dead)
			return (NULL);
		usleep(100);
	}
}

void
	ph_eat(t_philo *philo)
{
	philo->t_meal = current_t();
	philo_log(philo->info, get_t_diff(philo->info->t_start),
		philo->id + 1, EAT);
	ms_sleep(philo->info->t_eat, philo->info->t_start);
	drop_forks(*philo);
}

void
	ph_sleep(t_philo *philo)
{
	ms_sleep(philo->info->t_sleep, philo->info->t_start);
}

void
	ph_think(t_philo *philo)
{
	philo_log(philo->info, get_t_diff(philo->info->t_start),
		philo->id + 1, THINK);
	usleep(100);
}

void
	*philo_life(void *p)
{
	t_philo			*philo;
	pthread_t		life_thread;

	philo = (t_philo *)p;
	pthread_create(&life_thread, NULL, &life_checker, philo);
	shift_odd_philos(philo);
	while (philo->have_eaten != philo->info->n_meals)
	{
		take_forks(*philo);
		ph_eat(philo);
		philo->have_eaten += 1;
		if (philo->have_eaten == philo->info->n_meals)
		{
			philo->info->n_full_philos += 1;
			check_if_all_full(philo->info);
		}
		if (philo->info->is_dead)
		{
			pthread_join(life_thread, NULL);
			return (p);
		}
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}
