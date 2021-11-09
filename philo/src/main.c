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

	i = 0;
	while (i++ < 5)
		arr[i] = 0;
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
	if (i == 5)
		arr[4] = -1;
	return (1);
}

int
	main(int argc, char *argv[])
{
	int				arr[5];
	t_philo			*ph_arr;
	pthread_mutex_t	*forks;

	if (argc >= 5)
	{
		if (parse_args(argc, argv, arr))
		{
			forks = create_forks(arr[0]);
			ph_arr = (t_philo *)malloc(sizeof(t_philo *) * arr[0]);
			create_philos(arr, ph_arr, forks);
			launch_threads(ph_arr, arr[0]);
			join_threads(ph_arr, arr[0]);
		}
		else
			printf("Wrong program arguments\n");
	}
	else
	{
		printf("Not sufficient arguments. Do: ./philo n_of_philosophers " \
		"t_to_die t_to_eat t_to_sleep [n_each_philosopher_must_eat]\n");
	}
	return (0);
}
