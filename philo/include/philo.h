/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:27:51 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/02 11:27:52 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo {
	int			num;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat;
	uint64_t	t_start;
	pthread_t	pthread;
}	t_philo;

int			ft_atoi(const char *str);
uint64_t	tv_to_ms(struct timeval tv);
void		ms_sleep(uint64_t t_sleep);
uint64_t	get_t_diff(uint64_t start);

#endif