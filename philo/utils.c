/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:38:43 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/18 16:44:31 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(char *s)
{
	long	i;
	long	sign;
	long	sign_count;
	long	out;

	i = 0;
	sign = 1;
	sign_count = 0;
	out = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
		sign_count++;
	}
	while (s[i] >= '0' && s[i] <= '9' && sign_count < 2)
	{
		out = 10 * out + s[i] - '0';
		i++;
	}
	return (sign * out);
}
