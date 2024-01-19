/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:13:12 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/19 11:17:13 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_join(st->philos[i]->t, NULL); // like wait() but for threads
	}
	st->philos[i] = NULL;
}
