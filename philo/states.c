/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:06:21 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/12 09:38:13 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_start_eating(t_philo *phi)
{
	pthread_mutex_lock(phi->rf);
	put_message(MSG_FORK, phi);
	pthread_mutex_lock(&phi->lf);
	put_message(MSG_FORK, phi);
	put_message(MSG_EAT, phi);
	phi->eating = 1;
	if (phi->meals_left > 0)
		phi->meals_left--;
	return (0);
}

int	philo_start_sleeping(t_philo *phi)
{
	phi->eating = 0;
	pthread_mutex_unlock(&phi->lf);
	pthread_mutex_unlock(phi->rf);
	if (!phi->meals_left)
		return (1);
	put_message(MSG_SLEEP, phi);
	return (0);
}
