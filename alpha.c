#include "bool.h"
#include "alpha.h"

int
check_case(char letter, char lower_bound, char upper_bound)
{
    if ((letter >= lower_bound) && (letter <= upper_bound))
        return TRUE;
    else
        return FALSE;
}

int
check_lower_case(char letter)
{
    return check_case(letter, 'a', 'z');
}

char
lower2upper(char letter)
{
    if (check_lower_case(letter))
        return letter - 32;
    else
        return letter;
}

int
check_upper_case(char letter)
{
    return check_case(letter, 'A', 'Z');
}

char
upper2lower(char letter)
{
    if (check_upper_case(letter))
        return letter + 32;
    else
        return letter;
}

int
check_alpha(char letter)
{
    return check_lower_case(letter) || check_upper_case(letter);
}
