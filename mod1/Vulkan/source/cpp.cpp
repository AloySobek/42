/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:13:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/09 20:33:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class People
{
	public:
		double m_height;
		double m_weight;
		double m_money;

	private:
		int getWeight(double div)
		{
			if (div > 1.0)
				return (m_weight / div);
			return (m_weight);
		}

		int getHeight(double div)
		{
			if (div > 1.0)
				return (m_height / div);
			return (m_height);
		}
};

int main(int argc, char **argv)
{
	People Ben {11, 11 ,11};

	std::cout << Ben.m_money	<< std::endl;
	std::cout << Ben.m_height	<< std::endl;
	std::cout << Ben.m_weight	<< std::endl;
	return (0);
}