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

void	ft_usleep(int time_wait)
{
	struct timeval	tv;
	suseconds_t		time;
	long			time_refresh;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while (1)
	{
		usleep(500);
		gettimeofday(&tv, NULL);
		time_refresh = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - time;
		if (time_refresh >= time_wait)
			break ;
	}
	return ;
}
