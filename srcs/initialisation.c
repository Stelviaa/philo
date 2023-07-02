/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:56:11 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/02 16:42:45 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*routine(void *phil)
{
	t_philo *philo = (t_philo *)phil;
	first(philo);
	while (1)
	{
		if (philo->nbr_fork[0] == 0)
			take_fork(philo);
		if (philo->nbr_fork[0] == 2)
		{
			eat(philo);
			ft_usleep(philo->data->time_eat, philo->t_last_meal[0], philo);
		}
		if (philo->nbr_fork[0] == 3 && philo->data->time_eat < refresh_time(philo->data) - philo->t_last_meal[0])
		{
			sleeep(philo);
			ft_usleep(philo->data->time_sleep, philo->t_last_action[0], philo);
		}
		if (philo->nbr_fork[0] == 4 && philo->data->time_sleep < refresh_time(philo->data) - philo->t_last_action[0])
			think(philo);
		if (refresh_time(philo->data) - philo->t_last_meal[0] >= philo->data->time_die)
		{
			printf("%d %d died\n", refresh_time(philo->data), philo->index[0]);
			exit(1);
			break;
		}
	}
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
		philo->nbr_fork = malloc (sizeof(int));
		philo->nbr_fork[0] = 0;
		philo->index = malloc(sizeof(int));
		philo->index[0] = i;
		philo->t_last_action = malloc(sizeof(int));
		philo->t_last_action[0] = 0;
		philo->t_last_meal = malloc(sizeof(int));
		philo->t_last_meal[0] = 0;
		philo->data = data_gnl;
		philo->fork = malloc(sizeof(pthread_mutex_t));
		philo->id = malloc(sizeof(pthread_t));
		if (pthread_create(philo->id, NULL, &routine,(void *)philo) != 0)
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
		pthread_join(*philo->id, NULL);
		printf("%d\n", i);
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

void	ft_usleep(int	time_wait, int time_at_start, t_philo *philo)
{
	while (1)
	{
		usleep(50);
		if (refresh_time(philo->data) - time_at_start > time_wait)
			break;
	}
	return ;
}