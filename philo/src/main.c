/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:27:29 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/02 11:27:30 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int
	parse_args(int argc, char *argv[], int arr[])
{
	int	i;
	int	num;

	i = 1;
	while (i < argc)
	{
		if (i == 6)
			break ;
		num = ft_atoi(argv[i]);
		if (num < 0)
			return (0);
		arr[i - 1] = num;
		i++;
	}
	if (arr[4] < 0)
		return (0); //доработать выход с ошибкой
	if (i == 4)
		arr[4] = -1;
	return (1);
}

void
	create_philos(int arr[], t_philo *ph_arr, pthread_mutex_t *forks)
{
	int				i;
	struct timeval	tv;
	uint64_t		start;

	gettimeofday(&tv, NULL);
	start = tv_to_ms(tv);
	i = 0;
	while (i < arr[0])
	{
		ph_arr[i].n_philos = arr[0];
		ph_arr[i].id = i;
		ph_arr[i].t_die = arr[1];
		ph_arr[i].t_eat = arr[2];
		ph_arr[i].t_sleep = arr[3];
		if (arr[4] >= 0)
			ph_arr[i].n_meals = arr[4];
		else
			ph_arr[i].n_meals = -1;
		ph_arr[i].have_eaten = 0;
		ph_arr[i].t_start = start;
		ph_arr[i].forks = forks;
		pthread_mutex_init(&ph_arr[i].lock, NULL);
		ph_arr[i].ph_arr = (void **)ph_arr;
		i++;
	}
}

int
	main(int argc, char *argv[])
{
	int				arr[5];
	//int				i;
	t_philo			*ph_arr;
	pthread_mutex_t	*forks;

	if (argc >= 5)
	{
		if (parse_args(argc, argv, arr))
			printf("Hello, World!\n");
		else //change to correct exit:
		{
			printf("ERROR\n");
			exit(0);
		}
		forks = create_forks(arr[0]);
		ph_arr = (t_philo *)malloc(sizeof(t_philo *) * arr[0]);

		/*i = 0;
		while (i < arr[0])
		{
			ph_arr[i] = *(t_philo *)malloc(arr[0] * sizeof(t_philo));
			i++;
		}*/
		for(int i = 0; i < 5; ++i)
		{
			printf("%d\n", arr[i]);
		}
		create_philos(arr, ph_arr, forks);
		launch_threads(ph_arr, arr[0]);
		join_threads(ph_arr, arr[0]);
	}
	else
	{
		printf("Not sufficient arguments. Do: ./philo n_of_philosophers " \
		"t_to_die t_to_eat t_to_sleep [n_each_philosopher_must_eat]\n");
	}
	return (0);
}
