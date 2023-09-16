/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:47:44 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/16 14:29:48 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = init_struct_data(av, ac);
	if (data == NULL)
		return (0);
	set_time(data);
	philo = create_philo(data);
	is_died(philo);
	return (1);
}
