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



void *
	philo_life(void *philosopher)
{
	t_philo	philo;
	int i;

	philo = *(t_philo *)philosopher;
	i = philo.n_eat;
	while (i > 0)
	{
		printf("%llu %d is sleeping\n", get_t_diff(philo.t_start), philo.num);
		ms_sleep(philo.t_sleep * 1000);
		printf("%llu %d is eating\n", get_t_diff(philo.t_start), philo.num);
		ms_sleep(philo.t_eat * 1000);
		i--;
	}
	return (NULL);
}

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
	if (i == 4)
		arr[4] = -1;
	return (1);
}

void
	create_philos(int arr[], t_philo *ph_arr)
{
	int	i;
	struct timeval	tv;
	uint64_t start;
	t_philo	philo;

	gettimeofday(&tv, NULL);
	start = tv_to_ms(tv);
	i = 0;
	while (i < arr[0])
	{
		philo = ph_arr[i];
		philo.num = i + 1;
		philo.t_die = arr[1];
		philo.t_eat = arr[2];
		philo.t_sleep = arr[3];
		if (arr[4] >= 0)
			philo.n_eat = arr[4];
		philo.t_start = start;
		pthread_create(&philo.pthread, NULL, &philo_life, &philo);
		//pthread_join(th_philo, NULL);
		i++;
	}
}

int
	main(int argc, char *argv[])
{
	int	arr[5];
	int	i;
	t_philo *ph_arr;

	if (argc >= 5)
	{
		if (parse_args(argc, argv, arr))
			printf("Hello, World!\n");
		else //change to correct exit:
		{
			printf("ERROR\n");
			exit(0);
		}
	}
	ph_arr = (t_philo *) malloc(sizeof(t_philo) * arr[0]);
	for(int i = 0; i < 5; ++i)
	{
		printf("%d\n", arr[i]);
	}
	i = 0;
	create_philos(arr, ph_arr);
	i = 0;
	while (i < arr[0])
	{
		pthread_join(ph_arr[i].pthread, NULL);
		i++;
	}
	return (0);
}
