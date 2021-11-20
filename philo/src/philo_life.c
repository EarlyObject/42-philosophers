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
	ph_eat(t_philo *philo)
{
	uint64_t	t_meal;

	t_meal = get_t_diff(philo->info->t_start);
	philo->t_meal = t_meal;
	philo_log(philo->info, philo, philo->id + 1, EAT);
	ms_sleep(philo->info->t_eat, philo);
	philo->have_eaten += 1;
}

void
	ph_sleep(t_philo *philo)
{
	if (philo->info->t_sleep == 0)
		ms_sleep(1, philo);
	else
		ms_sleep(philo->info->t_sleep, philo);
}

void
	ph_think(t_philo *philo)
{
	philo_log(philo->info, philo, philo->id + 1, THINK);
	usleep(100);
}

void
	*philo_life(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (!philo->info->is_dead && philo->have_eaten != philo->info->n_meals)
	{
		take_forks(*philo);
		ph_eat(philo);
		drop_forks(*philo);
		if (philo->info->n_meals == 0 || philo->info->is_dead)
			break ;
		if (philo->have_eaten == philo->info->n_meals)
		{
			philo->info->n_full_philos += 1;
			check_if_all_full(philo->info);
		}
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}
