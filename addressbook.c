/*
 * addressbook.c
 *     See addressbook.h for documentation
 */

#include<stdio.h>
#include "bool.h"
#include "errno.h"
#include "addressbook.h"

void
die(int num_records)
{
    if (num_records < 1) {
        printf("Record could not be read/written. Error number: %d\n", errno);
    }
}

FILE *
open_db(char *mode)
{

    FILE *fp;

    if ((fp = fopen(ADDRESS_FILE, mode)) == NULL) {
        printf("Can't open address book. Error #: %d\n", errno);
        exit(1);
    }

    return fp;
}

void
read_address(FILE * fp, int index, struct address_entry *address)
{
    /* Seek to the record in the database */
    fseek(fp, index * sizeof(struct address_entry), SEEK_SET);

    die(fread(address, sizeof(struct address_entry), 1, fp));
}

void
update_address(FILE * fp, int index, struct address_entry *address)
{
    fseek(fp, index * sizeof(struct address_entry), SEEK_SET);

    die(fwrite(address, sizeof(struct address_entry), 1, fp));
}

void
delete_undelete_address(FILE * fp, int index, unsigned short int delete_flag)
{

    struct address_entry address;
    char action[10];

    if (delete_flag)
        strncpy(action, "Delete", 7);
    else
        strncpy(action, "Undelete", 7);

    read_address(fp, index, &address);
    address.deleted = delete_flag;
    update_address(fp, index, &address);

    printf("Address # %d has been %s\n\n", index, action);
}

void
delete_address(FILE * fp, int index)
{
    delete_undelete_address(fp, index, TRUE);
}

void
undelete_address(FILE * fp, int index)
{
    delete_undelete_address(fp, index, FALSE);
}

void
new_address(struct address_entry *address)
{
    FILE *fp;

    fp = open_db("a+");

    /* Go to the end of the database before adding a new entry */
    fseek(fp, 0, SEEK_END);

    die(fwrite(address, sizeof(struct address_entry), 1, fp));
    fclose(fp);
}

void
list_addresses(FILE * fp)
{
    int count = 0;
    struct address_entry address;
    char header_format[255];
    char row_format[255];

    /* Create format string for column headers */
    sprintf(header_format, "%%4s %%-%ds %%-%ds %%-%ds %%-%ds\n", FNAME_LENGTH,
            LNAME_LENGTH, EMAIL_LENGTH, PHONE_LENGTH);

    /* Create format string for rows */
    sprintf(row_format, "%%4d) %%-%ds %%-%ds %%-%ds %%-%ds\n", FNAME_LENGTH,
            LNAME_LENGTH, EMAIL_LENGTH, PHONE_LENGTH);

    /*  Print header */
    printf(header_format, "Index", "First Name", "Last Name", "Email",
           "Phone");

    /* Start at the beginning of the database */
    rewind(fp);

    /* Begin walking through the database */
    while (!feof(fp)) {
        fread(&address, sizeof(struct address_entry), 1, fp);
        if (!feof(fp)) {
            if (address.deleted) {
                printf(row_format, count, "Deleted", "", "", "");
            }
            else {
                /* Print rows */
                printf(row_format, count, address.fname, address.lname,
                       address.email, address.phone);
            }
            count++;
        }
    }
}
