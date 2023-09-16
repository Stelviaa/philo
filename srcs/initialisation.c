/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:56:11 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/16 14:31:08 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->index % 2 == 1)
		usleep(philo->data->nbr_p * 199);
	while (!philo->ok)
	{
		take_fork(philo);
		if (philo->nbr_fork == 2)
		{
			eat(philo);
			ft_usleep(philo->data->time_eat);
		}
		if (philo->nbr_fork == 3 && philo->data->time_eat - 1
			<= refresh_time(philo->data) - philo->t_last_meal)
		{
			sleeep(philo);
			ft_usleep(philo->data->time_sleep);
		}
		if (philo->nbr_fork == 4 && philo->data->time_sleep - 1
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
	philo->nbr_meal = 0;
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
	int				i;
	t_philo			*philo_begin;
	pthread_mutex_t	*display;
	pthread_mutex_t	*meal;
	t_philo			*philo;

	i = 0;
	philo = malloc(sizeof(t_philo));
	philo_begin = philo;
	display = malloc(sizeof(pthread_mutex_t));
	meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(display, NULL);
	pthread_mutex_init(meal, NULL);
	while (++i <= data_gnl->nbr_p)
	{
		philo->increment_meal = meal;
		init_philo(philo, display, data_gnl, i);
		if (i < data_gnl->nbr_p)
		{
			philo->next = malloc(sizeof(t_philo));
			philo = philo->next;
		}
	}
	philo->next = philo_begin;
	return (philo_begin);
}

int	verif_syntax(char **av)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	while (av[i])
	{
		while (av[i][y])
		{
			if (av[i][y] != 43 && (av[i][y] == 45
				|| av[i][y] > 57 || av[i][y] < 48))
				return (0);
			y ++;
		}
		y = 0;
		i ++;
	}
	return (1);
}

t_data	*init_struct_data(char	**av, int ac)
{
	t_data	*data;

	if (ac == 1 || (ac != 6 && ac != 5) || !verif_syntax(av))
	{
		printf ("Invalid Argument\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	data->nbr_p = ft_atoi(av[1]);
	if (data->nbr_p < 1)
	{
		printf ("Not good number of philosophers\n");
		free (data);
		return (0);
	}
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->nbr_philo_eat = 0;
	if (ac == 6)
		data->eat_limit = ft_atoi(av[5]);
	else
		data->eat_limit = -1;
	return (data);
}
