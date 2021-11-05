/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:11:49 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/02 12:11:50 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int
	calcrv(int sign, int count)
{
	if (sign < 0 && count > 0)
	{
		if (count == 2147483647)
			return (2147483647);
		return (0);
	}
	if (sign > 0 && count < 0)
	{
		if (count == -2147483648)
			return (-2147483648);
		return (-1);
	}
	return (count);
}

int
	ft_atoi(const char *str)
{
	int	sign;
	int	count;

	sign = 1;
	count = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13) || *str == 127)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		else
			sign = 1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		count *= 10;
		count += (*str - 48) * sign;
		str++;
	}
	return (calcrv(sign, count));
}

void
*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;

	dest = b;
	if (!b)
		return (NULL);
	while (len > 0)
	{
		*dest = (unsigned char)c;
		dest++;
		len--;
	}
	return (b);
}

void
ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}