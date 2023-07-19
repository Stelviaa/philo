/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:42:36 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/16 16:12:04 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork) == 0)
	{
		while (pthread_mutex_lock(philo->display))
			continue;
		printf("%d %d has taken a fork\n",
			refresh_time(philo->data), philo->index);
		pthread_mutex_unlock(philo->display);
		philo->nbr_fork ++;
	}
	if (pthread_mutex_lock(philo->next->fork) == 0)
	{	
		while (pthread_mutex_lock(philo->display))
			continue;
		printf("%d %d has taken a fork\n",
			refresh_time(philo->data),philo->index);
		pthread_mutex_unlock(philo->display);
		philo->nbr_fork ++;
	}
}

void	eat(t_philo *philo)
{
	philo->nbr_fork = 3;
	philo->t_last_meal = refresh_time(philo->data);
	while (pthread_mutex_lock(philo->display))
			continue;
	printf("%d %d is eating\n", refresh_time(philo->data), philo->index);
	pthread_mutex_unlock(philo->display);
}

void	sleeep(t_philo *philo)
{
	philo->nbr_meal ++;
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	philo->nbr_fork = 4;
	philo->t_last_action = refresh_time(philo->data);
	while (pthread_mutex_lock(philo->display))
			continue;
	printf("%d %d is sleeping\n", refresh_time(philo->data), philo->index);
	pthread_mutex_unlock(philo->display);
}

void	think(t_philo *philo)
{
	philo->nbr_fork = 0;
	while (pthread_mutex_lock(philo->display))
			continue;
	printf("%d %d is thinking\n", refresh_time(philo->data), philo->index);
	pthread_mutex_unlock(philo->display);
}

void	is_died(t_philo *philo)
{
	while(philo->data->eat_limit == -1
		|| philo->data->nbr_philo_eat != philo->data->nbr_p)
	{
		if (philo->data->eat_limit != -1 && philo->nbr_meal == philo->data->eat_limit)
		{
			while (pthread_mutex_lock(philo->increment_meal))
				continue;
			if (philo->ok == 0)
				philo->data->nbr_philo_eat ++;
			pthread_mutex_unlock(philo->increment_meal);
			philo->ok = 1;
		}
		if (refresh_time(philo->data) - philo->t_last_meal
			>= philo->data->time_die)
		{
			while (pthread_mutex_lock(philo->display))
				continue;
			printf("%d %d is died\n", refresh_time(philo->data), philo->index);
			return ;
		}
		philo = philo->next;
	}
	pthread_mutex_unlock(philo->display);
}
