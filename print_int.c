#include "holberton.h"
#include <stdlib.h>
#include <limits.h>

/**
 * print_int - Adds integers to our buffer
 * @args: pointer to the current va_arg
 * @flagstr: This a string of our flags, which we will apply
 *
 * Return: Our temporary buffer
 */
char *print_int(va_list args, char *flagstr)
{
	int ite, num, rem = 0, len = 0, is_negative = 0;
	unsigned int num_decoy, unsigned_num;

	char *tmpstring, *resultstring;

	if (args == NULL)
		return (NULL);
	tmpstring = _calloc(sizeof(int), 20);
	if (tmpstring == NULL)
		return (NULL);
	num = va_arg(args, int);
	num_decoy = num;
	if (num < 0)
	{
		num_decoy = -num;
		is_negative = 1;
	}
	unsigned_num = num_decoy;
	if (num == 0)
	{
		free(tmpstring);
		resultstring = _calloc(sizeof(int), 2);
		resultstring[0] = '0';
		return (resultstring);
	}
	while (num_decoy != 0)
		len++, num_decoy /= 10;
	for (ite = 0; ite < len; ite++)
	{
		rem = unsigned_num % 10;
		unsigned_num = unsigned_num / 10;
		tmpstring[len - (ite + 1)] = rem + '0';
	}
	tmpstring[len] = '\0';
	resultstring = flags_handler(flagstr, tmpstring, is_negative);
	free(tmpstring);
	if (resultstring == NULL)
		return (NULL);
	return (resultstring);
}

/**
 * flags_handler - This abomination checks our flags and sends a string to appl
 * @flags: A string of the flags we need to apply
 * @oristring: The original string of numbers which we're going to modify
 * @is_negative: An int that indicates wether or not our int was negative
 *
 * Return: an integer
 */
char *flags_handler(char *flags, char *oristring, int is_negative)
{
	int itef = 0;
	int flagstr[6] = {0, 0, 0, 0, 0, 0};
	char flag;
	int signage_done = 0, first_zero_seen = 0,
		precison_done = 0, short_long_done = 0;

	while (flags[itef] != '\0')
	{
		flag = flags[itef];
		if (flag == '+' && signage_done != 1)
			flagstr[1] = 1;
		else if (flag == ' ' && signage_done != 1)
			flagstr[2] = 1;
		else if (flag == '-' && signage_done != 1)
			flagstr[4] = 1;
		else if (flag == '0' && first_zero_seen != 1)
		{
			flagstr[3] = handles_zeros(itef, flags);
		signage_done = 1, first_zero_seen = 1, flag = flags[itef];
		}
		else if (flag >= '0' && flag <= '9')
		{
			flagstr[5] = handles_padding(itef, flags);
			signage_done = 1, flag = flags[itef];
		}
		else if (flag == '.' && precison_done != 1)
		{
			flagstr[0] = handles_zeros(itef, flags);
			precison_done = 1, signage_done = 1, flag = flags[itef];
		}
		else if ((flag == 'l' || flag == 'h') && short_long_done != 1)
			short_long_done = 1;
		else if (flag == 'd' || flag == 'i')
			short_long_done = 1;
		else
			return (NULL);
		itef++;
	}
	return (final_string_generator(oristring, flagstr, is_negative));
}

/**
 * final_string_generator - Apllies the flags according to the flagstr string
 * @oristring: The original string of numbers which we're going to modify
 * @flagstr: An array of ints which this function read to apply flags
 * @is_negative: An int that indicates wether or not our int was negative
 *
 * Return: an integer
 */
char *final_string_generator(char *oristring, int flagstr[], int is_negative)
{
	char *teststring, *resultstring;
	int zeros = 0, count = 0, spaces = 0, ite3 = 0;

	while (oristring[count] != '\0')
		count++;
	teststring = _calloc(sizeof(char), count + 1 + flagstr[3] +
	   flagstr[4] + flagstr[5] + 1);
	if (flagstr[0] != 0)
	{
		zeros = flagstr[0] - count;
		while (zeros > 0)
			teststring[ite3] = '0', zeros -= 1, ite3++, count++;
	}
	if (flagstr[1] != 0)
		teststring[ite3] = '+', count++;
	else if (flagstr[2] != 0)
		teststring[ite3] = ' ', count++;
	else if (is_negative == 1)
		teststring[ite3] = '-', count++;
	if (flagstr[3] != 0)
	{
		zeros = flagstr[3] - count;
		while (zeros > 0)
			teststring[ite3] = '0', zeros -= 1, ite3++, count++;
	}
	_strcat(teststring, oristring);
	if (flagstr[5] != 0)
		spaces = flagstr[5] - count;
	resultstring = _calloc(sizeof(char), (spaces + count + 1));
	if (flagstr[4] == 0)
	{
		for (ite3 = 0; spaces > 0; ite3++)
			resultstring[ite3] = ' ', spaces -= 1, count++;
	}
	_strcat(resultstring, teststring);
	free(teststring);
	while (spaces > 0)
		resultstring[count] = ' ', spaces -= 1, ite3++, count++;
	resultstring[count] = '\0';
	return (resultstring);
}
