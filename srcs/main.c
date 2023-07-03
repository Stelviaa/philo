/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:47:44 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/03 11:37:59 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;
	t_philo	*philo;

	i = 0;
	data = init_struct_data(av, ac);
	set_time(data);
	philo = create_philo(data);
	while (1)
	{
		if (refresh_time(philo->data) - philo->t_last_meal[0] >= philo->data->time_die)
		{
			printf("%d %d is died\n", refresh_time(data), philo->index[0]);
			while (++i <= data->nbr_p)
			{
				philo->died = 1;
				philo = philo->next;
			}
			return (0);
		}
		philo = philo->next;
	}
	return (1);
}
