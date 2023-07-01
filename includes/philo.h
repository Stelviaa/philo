/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:49:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/10 16:06:20 by sforesti         ###   ########.fr       */
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
	int				count_eat;
	int				nbr_p;
	suseconds_t		start_time;
}					t_data;

typedef struct s_philo {
	int				index;
	int				nbr_fork;
	int				t_last_meal;
	int				t_last_action;
	char			*status;
	t_data			*data;
	pthread_t		id;
	pthread_mutex_t	*fork;
	struct s_philo	*prev;
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
#endif