/*
 * alpha.h
 *     Very simple character library that deals with a alphabetic characters.
 */

/*
 * check_case
 *     Given a 'letter,' check the letter against the lower_bound and
 *     upper_bound.  If the letter is between the bounds or equal to either
 *     bound, this a TRUE (non-zero value) is returned. A FALSE (zero) is
 *     returned otherwise.
 */
int check_case(char letter, char lower_bound, char upper_bound);

/*
 * check_lower_case
 *     Given a 'letter,' check to see if that letter is lower case by using
 *     the 'check_case' function (whether bounds of ['a'...'z']). A TRUE
 *     (non-zero value) is returned if this is a lower case letter. A FALSE
 *     (zero) is returned otherwise.
 */
int check_lower_case(char letter);

/*
 * check_upper_case
 *     Given a 'letter,' check to see if that letter is upper case by using
 *     the 'check_case' function (whether bounds of ['A'...'Z']). A TRUE
 *     (non-zero value) is returned if this is an upper case letter. A FALSE
 *     (zero) is returned otherwise.
 */
int check_upper_case(char letter);

/*
 * check_alpha
 *     Given a 'letter,' check to see if that letter is an alphanumeric
 *     character (i.e., the character is either ['A'...'Z'] or ['a'...'z'].
 *     The check_lower_case and check_upper_case functions are used to
 *     accomplish this.  A TRUE (non-zero value) is returned if this is an
 *     upper case letter. A FALSE (zero) is returned otherwise.
 */
int check_alpha(char letter);

/* 
 * lower2upper
 *      Given a 'letter,' that letter is confirmed to be within the lower case
 *      range ['a'...'z']. If it is, it is converted to it's corresponding
 *      upper case letter.  If not, then the original letter is returned
 *      intact. The check_lower_case function is employed to assist in this
 *      conversion.
 */
char lower2upper(char letter);

/* 
 * upper2lower
 *      Given a 'letter,' that letter is confirmed to be within the upper case
 *      range ['A'...'Z']. If it is, it is converted to it's corresponding
 *      lower case letter.  If not, then the original letter is returned
 *      intact. The check_upper_case function is employed to assist in this
 *      conversion.
 */
char upper2lower(char letter);
