/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:56:11 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/12 12:50:56 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->index[0] % 2 == 0)
		usleep(100);
	while (philo->died == 0)
	{
		if (philo->nbr_fork[0] == 0 && philo->died == 0)
			take_fork(philo);
		if (philo->nbr_fork[0] == 2 && philo->died == 0)
		{
			eat(philo);
			usleep(philo->data->time_eat * 1000);
		}
		if (philo->nbr_fork[0] == 3 && philo->data->time_eat
			< refresh_time(philo->data) - philo->t_last_meal[0] && philo->died == 0)
		{
			sleeep(philo);
			usleep(philo->data->time_sleep * 1000);
		}
		if (philo->nbr_fork[0] == 4 && philo->data->time_sleep
			< refresh_time(philo->data) - philo->t_last_action[0] && philo->died == 0)
			think(philo);
	}
	return (NULL);
}

t_philo	*create_philo(t_data *data_gnl)
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
		philo->died = 0;
		philo->data = data_gnl;
		philo->fork = malloc(sizeof(pthread_mutex_t));
		philo->id = malloc(sizeof(pthread_t));
		if (pthread_create(philo->id, NULL, &routine, (void *)philo) != 0)
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
	int		i;
	t_philo	*tmp;

	i = 0;
	while (++i <= philo->data->nbr_p)
	{
		tmp = philo->next;
		if (i == 1)
			pthread_join(*philo->id, NULL);
		else
			pthread_join(*tmp->id, NULL);
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
	else
		data->count_eat = -1;
	return (data);
}
