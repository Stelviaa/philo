/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:49:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/16 15:30:37 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data {
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_limit;
	int				nbr_philo_eat;
	int				nbr_p;
	suseconds_t		start_time;
}					t_data;

typedef struct s_philo {
	int				index;
	int				nbr_fork;
	int				t_last_meal;
	int				t_last_action;
	int				nbr_meal;
	int				ok;
	t_data			*data;
	pthread_t		*id;
	pthread_mutex_t	*fork;
	pthread_mutex_t *display;
	pthread_mutex_t *increment_meal;
	struct s_philo	*next;
}					t_philo;

t_philo *create_philo(t_data *data);
void	*routine(void *phil);
int		ft_atoi(const char *str);
void	close_thread(t_philo *philo);
t_data	*init_struct_data(char	**av, int ac);
void	set_time(t_data *data);
int		refresh_time(t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
void	first(t_philo *philo);
void	take_fork(t_philo *philo);
void	eat(t_philo *philo);
void	sleeep(t_philo *philo);
void	think(t_philo *philo);
void	ft_usleep(int	time_wait);
void	is_died(t_philo *philo);
#endif