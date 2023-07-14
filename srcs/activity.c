/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:42:36 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/03 11:57:46 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	first(t_philo *philo)
{
	if (!pthread_mutex_lock(philo->fork)
		&& !pthread_mutex_lock(philo->next->fork))
	{
		printf("%d %d has taken a fork\n", refresh_time(philo->data),philo->index[0]);
		printf("%d %d has taken a fork\n", refresh_time(philo->data),philo->index[0]);
		philo->nbr_fork[0] += 2;
	}
	else
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
	}
}

void	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork) == 0)
	{
		while (pthread_mutex_lock(philo->display))
			continue;
		printf("%d %d has taken a fork\n", refresh_time(philo->data),philo->index[0]);
		pthread_mutex_unlock(philo->display);
		philo->nbr_fork[0] ++;
	}
	if (pthread_mutex_lock(philo->next->fork) == 0)
	{	while (pthread_mutex_lock(philo->display))
			continue;
		printf("%d %d has taken a fork\n", refresh_time(philo->data),philo->index[0]);
		philo->nbr_fork[0] ++;
	}
}

void	eat(t_philo *philo)
{
	int	time;

	time = refresh_time(philo->data);
	philo->nbr_fork[0] = 3;
	philo->t_last_meal[0] = time;
	while (pthread_mutex_lock(philo->display))
			continue;
	printf("%d %d is eating\n", time, philo->index[0]);
	pthread_mutex_unlock(philo->display);

}

void	sleeep(t_philo *philo)
{
	int	time;

	time = refresh_time(philo->data);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	philo->nbr_fork[0] = 4;
	philo->t_last_action[0] = time;
	while (pthread_mutex_lock(philo->display))
			continue;
	printf("%d %d is sleeping\n", time, philo->index[0]);
	pthread_mutex_unlock(philo->display);
}

void	think(t_philo *philo)
{
	philo->nbr_fork[0] = 0;
	while (pthread_mutex_lock(philo->display))
			continue;
	printf("%d %d is thinking\n", refresh_time(philo->data), philo->index[0]);
	pthread_mutex_unlock(philo->display);
}