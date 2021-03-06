/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:27:51 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/21 09:57:51 by asydykna         ###   ########.fr       */
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

# define LEFT 1
# define RIGHT 2
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

typedef struct s_info {
	int				n_philos;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				n_meals;
	uint64_t		t_start;
	bool			is_dead;
	pthread_mutex_t	*lock;
	int				n_full_philos;
}	t_info;

typedef struct s_philo {
	int				id;
	int				have_eaten;
	uint64_t		t_meal;
	t_info			*info;
	pthread_t		pthread;
	pthread_mutex_t	*forks;
	struct s_philo	*ph_arr;
}	t_philo;

int				ft_atoi(const char *str);
void			ms_sleep(uint64_t t_sleep, t_philo *philo);
uint64_t		get_t_diff(uint64_t start);
uint64_t		current_t(void );
void			launch_threads(t_philo *ph_arr, int n_philos);
void			join_threads(t_philo *ph_arr, int n_philos);
void			*philo_life(void *p);
pthread_mutex_t	*create_forks(int n_forks);
void			take_fork(t_philo ph, int fork);
void			take_forks(t_philo philo);
void			drop_forks(t_philo philo);
void			philo_log(t_info *info, t_philo *philo, int ph_id, int action);
void			philo_log_death(int ph_id, t_info *info);
void			check_if_all_full(t_info *info);
void			create_philos(int arr[], t_philo *ph_arr,
					pthread_mutex_t *forks);
void			life_indicator(t_info *info, t_philo *p);
void			philo_log_fork(t_info *info, int ph_id);

#endif