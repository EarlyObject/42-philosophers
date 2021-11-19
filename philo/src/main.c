/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:27:29 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/10 13:43:46 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void
	my_leaks(void)
{
	system("leaks philo");
}

int
	check_args(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

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
		if (!check_args(argv[i]))
			return (0);
		num = ft_atoi(argv[i]);
		if (num < 0)
			return (0);
		arr[i - 1] = num;
		i++;
	}
	if (arr[0] <= 0 || arr[0] > 200)
		return (0);
	if (i == 5)
		arr[4] = -1;
	return (1);
}

void
	clean_mem(pthread_mutex_t *forks, t_philo *ph_arr, t_info *info)
{
	free(forks);
	free(ph_arr);
	free(info->lock);
	free(info);
}

int
	main(int argc, char *argv[])
{
	int				arr[5];
	t_philo			*ph_arr;
	pthread_mutex_t	*forks;

	if (argc >= 5 && argc <= 6)
	{
		if (parse_args(argc, argv, arr))
		{
			forks = create_forks(arr[0]);
			ph_arr = (t_philo *)malloc(sizeof(t_philo) * arr[0]);
			create_philos(arr, ph_arr, forks);
			launch_threads(ph_arr, arr[0]);
			join_threads(ph_arr, arr[0]);
			clean_mem(forks, ph_arr, ph_arr[0].info);
		}
		else
			printf("Wrong program arguments\n");
	}
	else
	{
		printf("Wrong arguments. Do: ./philo n_of_philosophers " \
		"t_to_die t_to_eat t_to_sleep [n_each_philosopher_must_eat]\n");
	}
	return (0);
}
