/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:22:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/01 19:58:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
 
#define BASE 10 //система счисления
#define MIN_LENGTH_FOR_KARATSUBA 4 //числа короче умножаются квадратичным алгоритмом
 
long_value karatsuba(long_value a, long_value b) {
  long_value product; //результирующее произведение
  product.length = a.length + b.length;
  product.values = new digit[product.length];
 
  if (a.length < MIN_LENGTH_FOR_KARATSUBA) { //если число короче то применять наивное умножение
    memset(product.values, 0, sizeof(digit) * product.length);
    for (size_length i = 0; i < a.length; ++i)
      for (size_length j = 0; j < b.length; ++j) {
        product.values[i + j] += a.values[i] * b.values[j];
        /*В случае изменения MIN_LENGTH_FOR_KARATSUBA или BASE расскоментировать следующие
        * строки и подобрать соотв. значения для исключения переполнения разрядов.
        * Например для десятичной системы счисления число 100, означает, что организовавается
        * перенос 1 через один разряд, 200 - перенос 2 через один разрряд, 5000 - 5 через два.
        * if (product.values[i + j] >= 100){
        *   product.values[i + j] -= 100;
        *   product.values[i + j + 2] += 1;
        * }
        */
      }
  } else { //умножение методом Карацубы
    long_value a_part1; //младшая часть числа a
    a_part1.values = a.values;
    a_part1.length = (a.length + 1) / 2;
 
    long_value a_part2; //старшая часть числа a
    a_part2.values = a.values + a_part1.length;
    a_part2.length = a.length / 2;
 
    long_value b_part1; //младшая часть числа b
    b_part1.values = b.values;
    b_part1.length = (b.length + 1) / 2;
 
    long_value b_part2; //старшая часть числа b
    b_part2.values = b.values + b_part1.length;
    b_part2.length = b.length / 2;
 
    long_value sum_of_a_parts = sum(a_part1, a_part2); //cумма частей числа a
    normalize(sum_of_a_parts);
    long_value sum_of_b_parts = sum(b_part1, b_part2); //cумма частей числа b
    normalize(sum_of_b_parts);
    long_value product_of_sums_of_parts = karatsuba(sum_of_a_parts, sum_of_b_parts);
    // произведение сумм частей
 
    long_value product_of_first_parts = karatsuba(a_part1, b_part1); //младший член
    long_value product_of_second_parts = karatsuba(a_part2, b_part2); //старший член
    long_value sum_of_middle_terms = sub(sub(product_of_sums_of_parts, product_of_first_parts), product_of_second_parts);
    //нахождение суммы средних членов
 
    /*
    * Суммирование многочлена
    */
    memcpy(product.values, product_of_first_parts.values,
      product_of_first_parts.length * sizeof(digit));
    memcpy(product.values + product_of_first_parts.length,
      product_of_second_parts.values, product_of_second_parts.length
      * sizeof(digit));
    for (size_length i = 0; i < sum_of_middle_terms.length; ++i)
      product.values[a_part1.length + i] += sum_of_middle_terms.values[i];
 
    /*
    * Зачистка
    */
    delete [] sum_of_a_parts.values;
    delete [] sum_of_b_parts.values;
    delete [] product_of_sums_of_parts.values;
    delete [] product_of_first_parts.values;
    delete [] product_of_second_parts.values;
  }
 
  normalize(product); //конечная нормализация числа
 
  return product;
}
