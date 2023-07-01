/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:56:11 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/10 16:04:11 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	first(t_philo *philo)
{
	if (!pthread_mutex_lock(philo->fork)
		&& !pthread_mutex_lock(philo->next->fork))
	{
		philo->status = ft_strdup("has taken a fork");
		printf("%d %d %s\n", refresh_time(philo->data),philo->index, philo->status);
		printf("%d %d %s\n", refresh_time(philo->data),philo->index, philo->status);
		philo->nbr_fork += 2;
	}
}

void	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork) == 0)
	{
		if (philo->status != NULL)
			free(philo->status);
		philo->status = ft_strdup("has taken a fork");
		printf("%d %d %s\n", refresh_time(philo->data),philo->index, philo->status);
		philo->nbr_fork ++;
	}
	if (pthread_mutex_lock(philo->next->fork) == 0)
	{
		if (philo->next->status != NULL)
			free(philo->next->status);
		philo->next->status = ft_strdup("has taken a fork");
		philo->nbr_fork ++;
	}
}

void	eat(t_philo *philo)
{
	int	time;

	time = refresh_time(philo->data);
	if (philo->status)
		free(philo->status);
	philo->status = ft_strdup("is eating");
	philo->nbr_fork = 3;
	philo->t_last_meal = time;
	printf("%d %d %s\n", time, philo->index, philo->status);

}

void	sleeep(t_philo *philo)
{
	int	time;

	time = refresh_time(philo->data);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	if (philo->status)
		free(philo->status);
	philo->nbr_fork = 4;
	philo->t_last_action = time;
	philo->status = ft_strdup("is sleeping");
	printf("%d %d %s\n", time, philo->index, philo->status);
}

void	*routine(void *phil)
{
	t_philo *philo = (t_philo *)phil;
	first(philo);
	while (1)
	{
		if (philo->nbr_fork == 2)
			eat(philo);
		if (philo->nbr_fork == 3 && philo->data->time_eat < refresh_time(philo->data) - philo->t_last_meal)
			sleeep(philo);
		if (philo->nbr_fork == 4 && philo->data->time_sleep < refresh_time(philo->data) - philo->t_last_action)
		{
			if (philo->status)
				free(philo->status);
			philo->status = ft_strdup("is thinking");
			philo->nbr_fork = 0;
			printf("%d %d %s\n", refresh_time(philo->data), philo->index, philo->status);
		}
		if (refresh_time(philo->data) - philo->t_last_meal >= philo->data->time_die)
			break;
		take_fork(philo);
	}
	//close_thread(philo);
	// usleep(30);
	return (NULL);
}

t_philo 	*create_philo(t_data *data_gnl)
{
	int		i;
	t_philo	*philo_begin;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo));
	philo_begin = philo;
	while (++i <= data_gnl->nbr_p)
	{
		philo->nbr_fork = 0;
		philo->index = i;
		philo->status = NULL;
		philo->data = data_gnl;
		philo->fork = malloc(sizeof(pthread_mutex_t));
		if (pthread_create(&philo->id, NULL, &routine,(void *)philo) != 0)
			printf("Error pthread create\n");
		if (pthread_mutex_init(philo->fork, NULL))
			printf("Error pthread mutex create\n");
		if (i < data_gnl->nbr_p)
		{
			philo->next = malloc(sizeof(t_philo));
			philo->next->prev = philo;
			philo = philo->next;
		}
	}
	philo->next = philo_begin;
	philo_begin->prev = philo;
	return (philo_begin);
}

void	close_thread(t_philo *philo)
{
	int i;

	i = 0;
	while (++i <= philo->data->nbr_p)
	{
		pthread_join(philo->id, NULL);
		philo = philo->next;
	}
}

t_data	*init_struct_data(char	**av, int ac)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->nbr_p = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->count_eat = ft_atoi(av[5]);
	return (data);
}

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
