/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_mngmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:43:07 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/10 13:43:54 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*struct timeval
	current_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv);
}*/

uint64_t
	current_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + (tv.tv_usec / 1000));
}

void
	ms_sleep(uint64_t t_sleep, uint64_t start)
{
	uint64_t	start_ts;
	uint64_t	sleep_time;

	start_ts = get_t_diff(start);
	sleep_time = start_ts + t_sleep;
	while (get_t_diff(start) < sleep_time)
		usleep(100);
}

/*uint64_t
	get_t_diff(struct timeval start)
{
	struct timeval	tv;
	uint64_t		sec;
	uint64_t		ms;
	uint64_t		ms_final;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec - start.tv_sec;
	ms = tv.tv_usec - start.tv_usec;
	ms_final = sec * 1000000 + ms;
	return (ms_final / 1000);
}*/

uint64_t
	get_t_diff(uint64_t start)
{
	return (current_t() - start);
}

void
	shift_odd_philos(const t_philo *philo)
{
	if (philo->id % 2)
		usleep(200);
}
