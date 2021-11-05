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
	int				n_philos;
	int				id;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int 			have_eaten;
	uint64_t		t_start;
	pthread_t		pthread;
	pthread_mutex_t	*forks;
	int				**i_forks;
	pthread_mutex_t	lock;
	void 			*ph_arr;
}	t_philo;

int				ft_atoi(const char *str);
uint64_t		tv_to_ms(struct timeval tv);
void			ms_sleep(uint64_t t_sleep);
uint64_t		get_t_diff(uint64_t start);
void			launch_threads(t_philo *ph_arr, int n_philos);
void			join_threads(t_philo *ph_arr, int n_philos);
void			*philo_life(void *philosopher);
pthread_mutex_t	*create_forks(int n_forks);
void			take_fork(t_philo philo, char c);
void			*ft_calloc(size_t count, size_t size);



#endif