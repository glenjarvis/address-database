
#include<stdio.h>

#define ADDRESS_FILE "addressbook.dat"

#define FNAME_LENGTH 15
#define LNAME_LENGTH 15
#define EMAIL_LENGTH 20         /* Technically, this can be 256. But, this */
                                /* is good enough for us for this example. */
#define PHONE_LENGTH 15

struct address_entry {
    unsigned short int deleted;
    char fname[FNAME_LENGTH];
    char lname[LNAME_LENGTH];
    char email[EMAIL_LENGTH];
    char phone[PHONE_LENGTH];
};

/*
 * die
 *     Check for number of records read. If less than 1, report an error and
 *     the errno. This is an easy check for validity of funciton execution
 *      without spending a large amount of effort.
 *
 *     This is intended to be an internal function and not really meant to
 *     be used directly as part of the API.
 */
void die(int num_records);

/*
 * open_db
 *     Given a string to indicate mode, Open file defined in ADDRESS_FILE.
 *     Return pointer to  file.
 */
FILE *open_db(char *mode);

/*
 * read_address
 *     Given an open file pointer, the index into the database, and a pointer
 *     where to place the read data, read the record directly into the
 *     structure.
 *
 *     Report errors and quit (see die) if record is not read.
 */
void read_address(FILE * fp, int index, struct address_entry *address);

/*
 * update_address
 *     Given an open file pointer, the index into the database, and a pointer
 *     where to place the read data, update the record in the file pointed
 *     to by open file pointer.
 *
 *     Report errors and quit (see die) if record is not read.
 */
void update_address(FILE * fp, int index, struct address_entry *address);

/*
 * delete_undelete_address
 *     Given an open file pointer, the index into the database, and TRUE/FALSE
 *     flag, update the address with the FLAG given.
 *
 *     This is intended to be an internal function and not really meant to
 *     be used directly as part of the API. Use delete_address and
 *     undelete_address instead.  
 */
void delete_undelete_address(FILE * fp, int index,
                             unsigned short int delete_flag);

/*
 * delete_address
 *     Given an open file pointer and the index into the database, update the
 *     delete flag to be deleted. This routine does not currently first check
 *     if the flag is already deleted before rewriting to record back to file.
 */
void delete_address(FILE * fp, int index);

/*
 * undelete_address
 *     Given an open file pointer and the index into the database, update the
 *     delete flag to be undeleted. This routine does not currently first check
 *     if the flag is already undeleted before rewriting to record back to
 *     file.
 */
void undelete_address(FILE * fp, int index);

/*
 * new_address
 *     Given a pointer to the address_entry struct, that entry will be
 *     written at the end of the database file defined in ADDRESS_FILE. See
 *     also open_db.
 */
void new_address(struct address_entry *address);

/*
 * list_addresses
 *     Scan file indicated by ADDRESS_FILE from beginning to end, printing a
 *     summary of each record (one per line) and an index number that refers
 *     to that record in the database.
 */
void list_addresses(FILE * fp);
