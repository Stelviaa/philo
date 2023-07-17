/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:56:11 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/16 16:44:04 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->index % 2 == 0)
	 	usleep(500);
	while (1)
	{
		if (philo->nbr_fork == 0)
			take_fork(philo);
		if (philo->nbr_fork == 2)
		{
			eat(philo);
			ft_usleep(philo->data->time_eat - 1);
		}
		if (philo->nbr_fork == 3 && philo->data->time_eat
			<= refresh_time(philo->data) - philo->t_last_meal)
		{
			sleeep(philo);
			ft_usleep(philo->data->time_sleep - 1);
		}
		if (philo->nbr_fork == 4 && philo->data->time_sleep
			<= refresh_time(philo->data) - philo->t_last_action)
			think(philo);
	}
	return (NULL);
}

void	init_philo(t_philo *philo, pthread_mutex_t *displ, t_data *data, int i)
{
	philo->nbr_fork = 0;
	philo->index = i;
	philo->t_last_action = 0;
	philo->t_last_meal = 0;
	philo->display = displ;
	philo->count_meal = 0;
	philo->data = data;
	philo->ok = 0;
	philo->fork = malloc(sizeof(pthread_mutex_t));
	philo->id = malloc(sizeof(pthread_t));
	pthread_mutex_init(philo->fork, NULL);
	if (pthread_create(philo->id, NULL, &routine, (void *)philo) != 0)
		printf("Error pthread create\n");
}

t_philo	*create_philo(t_data *data_gnl)
{
	int		i;
	t_philo	*philo_begin;
	pthread_mutex_t *display;
	t_philo	*philo;
	
	i = 0;
	philo = malloc(sizeof(t_philo));
	philo_begin = philo;
	display = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(display, NULL))
		printf("Error pthread mutex create\n");
	while (++i <= data_gnl->nbr_p)
	{
		init_philo(philo, display, data_gnl, i);
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
		if (i == 1)
		{
			tmp = philo->next;
			pthread_join(*philo->id, NULL);
		}
		else
		{	
			tmp = tmp->next;
			pthread_join(*tmp->prev->id, NULL);
		}
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
	data->nbr_meal = 0;
	if (ac == 6)
		data->count_eat = ft_atoi(av[5]);
	else
		data->count_eat = -1;
	return (data);
}
