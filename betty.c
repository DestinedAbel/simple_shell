#include <stdio.h>
#include <time.h>

#define INFANT_MAX_MONTHS 12
#define TODDLER_MAX_YEARS 5
#define CHILD_MAX_YEARS 12
#define TEENAGER_MAX_YEARS 19

/**
 * calculate_age - Calculates the age based on the birth year provided.
 *
 * @birth_year: The year the user was born.
 * Return: The calculated age.
 */
int calculate_age(int birth_year)
{
	time_t current_time = time(NULL);
	struct tm *current_date = localtime(&current_time);
	int current_year = current_date->tm_year + 1900;

	return (current_year - birth_year);
}

/**
 * get_age_group - Determines age group
 * Determines the age group based on the given age.
 *
 * @age: The calculated age.
 * Return: The age group as a string.
 */
const char *get_age_group(int age)
{
	if (age <= INFANT_MAX_MONTHS)
		return ("Infant");
	else if (age <= TODDLER_MAX_YEARS)
		return ("Toddler");
	else if (age <= CHILD_MAX_YEARS)
		return ("Child");
	else if (age <= TEENAGER_MAX_YEARS)
		return ("Teenager");
	else
		return ("Adult");
}

/**
 * int_main - Calculate the user's age and age group.
 *
 * @main: the main function
 *
 * Return: nothing
 */
int main(void)
{
	int birth_year;
	int age;
	const char *age_group;

	printf("Enter the year you were born: ");
	scanf("%d", &birth_year);

	age = calculate_age(birth_year);
	age_group = get_age_group(age);

	printf("Your age is %d\n", age);
	printf("Your age group is %s\n", age_group);

	return (0);
}
