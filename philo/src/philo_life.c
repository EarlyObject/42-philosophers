/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:14:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/04 12:14:15 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	*life_checker(void *p_philo)
{
	t_philo		*philo;
	uint64_t	t_current;

	philo = (t_philo *)p_philo;
	while (true)
	{
		t_current = current_t();
		if (!pthread_mutex_lock(philo->info->lock))
		{
			if ((int)(t_current - philo->t_meal) >= philo->info->t_die)
			{
				if (!(philo->info->is_dead))
				{
					philo_log(philo->info, get_t_diff(philo->info->t_start), philo->id + 1, DIE, philo->info->is_dead);
					philo->info->is_dead = true;
				}
				pthread_mutex_unlock(philo->info->lock);
				return (NULL);
			}
		}
		pthread_mutex_unlock(philo->info->lock);
		if (philo->info->is_dead)
			return (NULL);
	}
}

void
	ph_eat(t_philo *philo)
{
	philo->t_meal = current_t();
	philo_log(philo->info, get_t_diff(philo->info->t_start), philo->id + 1, EAT, philo->info->is_dead);
	ms_sleep((philo)->info->t_eat);
	drop_forks(*philo);
}

void
	ph_sleep(t_philo *philo)
{
	philo_log(philo->info, get_t_diff(philo->info->t_start), philo->id + 1, SLEEP, philo->info->is_dead);
	ms_sleep(philo->info->t_sleep);
}

void
	ph_think(t_philo *philo)
{
	philo_log(philo->info, get_t_diff(philo->info->t_start), philo->id + 1, THINK, philo->info->is_dead);
	usleep(100);
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

void *
	philo_life(void *p)
{
	t_philo			*philo;
	pthread_t		life_thread;

	philo = (t_philo *)p;
	pthread_create(&life_thread, NULL, &life_checker, philo);
	while (philo->have_eaten != philo->info->n_meals)
	{
		take_forks(*philo);
	/*	uint64_t	t_current;
		t_current = current_t();
		if ((int)(t_current - philo->t_meal) >= philo->info->t_die)
		{
			pthread_join(*philo->life_thread, NULL);
		}*/
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
			return (p); //NULL?
		}
		ph_sleep(philo);
		ph_think(philo);
		printf("%d have eaten %d times\n", philo->id + 1, philo->have_eaten);
	}
	return (NULL);
}
