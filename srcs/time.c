/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:10:39 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/16 14:03:51 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	refresh_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - data->start_time);
}

suseconds_t	set_time_u()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	refresh_time_u(start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time);
}

void	ft_usleep(int time_wait)
{
	suseconds_t		start_time;
	
	start_time = set_time_u();
	while (1)
	{
		usleep(300);
		if (refresh_time_u(start_time) >= time_wait)
			break ;
	}
	return ;
}
