#include <unistd.h>
#include <string.h>
#include "pilab-string.h"

/*
 * Converts string to upper case.
 */

void string_to_upper(char *string)
{
	while (*string) {
		if (*string >= 'a' && *string <= 'z')
			*string &= ~(1UL << 5);
		string++;
	}
}

/*
 * Converts string to lower case.
 */

void string_to_lower(char *string)
{
	while (*string) {
		if (*string >= 'A' && *string <= 'Z')
			*string |= 1UL << 5;
		string++;
	}
}

/*
 * Compares two ASCII chars (case independent).
 *
 * Returns:
 *   -1: string1 < string2
 *    0: string1 == string2
 *    1: string1 > string2
 */

int string_charcasecmp(const char *string1, const char *string2)
{
	size_t wchar1, wchar2;

    if (!string1 || !string2)
        return (string1) ? 1 : ((string2) ? -1 : 0);

	wchar1 = *string1;
    if ((wchar1 >= 'A') && (wchar1 <= 'Z'))
        wchar1 += ('a' - 'A');

	wchar2 = *string2;
    if ((wchar2 >= 'A') && (wchar2 <= 'Z'))
        wchar2 += ('a' - 'A');

    return (wchar1 < wchar2) ? -1 : ((wchar1 == wchar2) ? 0 : 1);
}

/*
 * Compares two ASCII chars (case dependent).
 *
 * Returns:
 * -1: string1 < string2
 *  0: string1 == string2
 *  1: string1 > string2
 */

int string_charcmp(const char *string1, const char *string2)
{
	size_t wchar1, wchar2;

	if (!string1 || !string2)
		return (string1) ? 1 : ((string2) ? -1 : 0);
	wchar1 = *string1;
	wchar2 = *string2;
	return (wchar1 < wchar2) ? -1 : ((wchar1 == wchar2) ? 0 : 1);
}

/*
 * Compares two strings (case independent).
 *
 * Returns:
 * -1: string1 < string2
 *  0: string1 == string2
 *  1: string1 > string2
 */

int string_strcasecmp(const char *string1, const char *string2)
{
	size_t diff, slen1, slen2;

	if (!string1 || !string2)
		return (string1) ? 1 : ((string2) ? -1 : 0);

	slen1 = strlen(string1);
	slen2 = strlen(string2);

	if (slen1 != slen2)
		return (slen1 < slen2) ? -1 : 1;

	while (*string1 && *string2) {
		diff = string_charcasecmp(string1, string2);
		if (diff != 0)
			return diff;
		string1++;
		string2++;
	}
	return 0;
}

/*
 * Compares two strings with the first n bytes (case dependent).
 *
 * Returns:
 *    -1: string1 < string2
 *     0: string1 == string2
 *     1: string1 > string2
 */

int string_strcmp(const char *string1, const char *string2)
{
	size_t diff, slen1, slen2;

	if (!string1 || !string2)
		return (string1) ? 1 : ((string2) ? -1 : 0);

	slen1 = strlen(string1);
	slen2 = strlen(string2);

	if (slen1 != slen2)
		return (slen1 < slen2) ? -1 : 1;

	while (*string1 && *string2) {
		diff = string_charcmp(string1, string2);
		if (diff != 0)
			return diff;
		string1++;
		string2++;
	}
	return 0;
}

/*
 * Compares two strings with the first n bytes (case dependent).
 *
 * Returns:
 *    -1: string1 < string2
 *     0: string1 == string2
 *     1: string1 > string2
 */

int string_strncmp(const char *string1, const char *string2, size_t n)
{
	size_t diff, slen1, slen2, count;

	if (!string1 || !string2)
		return (string1) ? 1 : ((string2) ? -1 : 0);

	count = 0;
	while (count < n && *string1 && *string2) {
		diff = string_charcmp(string1, string2);
		if (diff != 0)
			return diff;
		string1++;
		string2++;
		count++;
	}

	slen1 = strlen(string1);
	slen2 = strlen(string2);

	if (slen1 != slen2)
		return (slen1 < slen2) ? -1 : 1;

	if (count >= n)
		return 0;

	return slen1 < slen2 ? -1 : ((slen1 > slen2) ? 1 : 0);
}
