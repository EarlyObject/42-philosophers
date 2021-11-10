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

uint64_t
	tv_to_ms(struct timeval tv)
{
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

uint64_t
	current_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv_to_ms(tv));
}

void
	ms_sleep(uint64_t t_sleep)
{
	struct timeval	tv;
	uint64_t		start_t;

	gettimeofday(&tv, NULL);
	start_t = tv_to_ms(tv);
	while (true)
	{
		usleep(50);
		if (current_t() - start_t >= t_sleep)
			return ;
	}
}

uint64_t
	get_t_diff(uint64_t start)
{
	struct timeval	tv;
	uint64_t		time_now;

	gettimeofday(&tv, NULL);
	time_now = tv_to_ms(tv);
	return (time_now - start);
}
