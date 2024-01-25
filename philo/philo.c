/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:13:12 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/25 09:22:56 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/2 ou 1/3 philo prend les fourchettes et mange
// on switch a droite

void	*output_thread(void *vargp)
{
	printf("thread created! (%p)\n", vargp);
	return (NULL);
}

void	create_philos(t_stats *st)
{
	int	i;

	st->philos = malloc((st->n_philos + 1) * sizeof(t_philo *));
	i = -1;
	while (++i < st->n_philos)
	{
		st->philos[i] = malloc(sizeof(t_philo));
		pthread_create(&st->philos[i]->t, NULL, output_thread, st->philos[i]);
		pthread_mutex_init(&st->philos[i]->fork, NULL);
		pthread_join(st->philos[i]->t, NULL);
	}
	st->philos[i] = NULL;
}
