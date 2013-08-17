
#include <stdio.h>
#include <errno.h>
#include "bool.h"
#include "alpha.h"
#include "addressbook.h"

#define MAX_BUFFER_SIZE 255

int get_index(char *action);
void list_index();
void delete(FILE * fp);
void undelete(FILE * fp);
void new(struct address_entry *address);
void update_field(char *attribute, char *field, int max_size,
                  unsigned short int new);
void edit_address(FILE * fp);

int
menu(void)
{
    char choice = '\0';

    printf("************************************************************\n");
    printf("*                  Address Database Menu                   *\n");
    printf("************************************************************\n");

    printf("I) List Index (Table of Contents) of database               \n");
    printf("D) Delete an entry.                                         \n");
    printf("U) Undelete an entry.                                       \n");
    printf("N) Enter a New address                                      \n");
    printf("E) Edit an Existing address                                 \n");
    printf("Q) Quit the program                                         \n");
    printf("\n\n");
    printf("choice (and press ENTER)> ");

    choice = getchar();         /* Take first character from input */
    while (getchar() != '\n') ; /* Eat rest of line since they pressed ENTER */
    return lower2upper(choice);
}

int
get_index(char *action)
{
    int index;

    printf("Which index number do you wish to %s?\n", action);
    printf("choice> ");
    scanf("%d", &index);
    while (getchar() != '\n') ; /* Eat rest of line since they pressed ENTER */

    return index;
}

void
list_index(FILE * fp)
{
    printf("Addresses\n");
    printf("=========\n");
    list_addresses(fp);
    printf("\n\n");
}

void
delete(FILE * fp)
{
    int index;

    index = get_index("delete");
    delete_address(fp, index);
    printf("\n\n");
}

void
undelete(FILE * fp)
{
    int index;

    index = get_index("undelete");
    undelete_address(fp, index);
    printf("\n\n");
}

void
new(struct address_entry *address)
{
    printf("New Address\n");
    printf("===========\n\n");

    update_field("First Name", address->fname, FNAME_LENGTH, TRUE);
    update_field("Last Name", address->lname, LNAME_LENGTH, TRUE);
    update_field("Email", address->email, EMAIL_LENGTH, TRUE);
    update_field("Phone", address->phone, PHONE_LENGTH, TRUE);

    address->deleted = FALSE;
    new_address(address);
}

void
clean_buffer(char *buffer)
{
    char *buffer_ptr = buffer;
    int i = 0;

    for (i = 0; i < MAX_BUFFER_SIZE; i++) {
        /* If we find a new line character, replace with
         * a null so that this is a string. And, we can
         * bail (done early)
         */
        if (*(buffer_ptr + i) == '\n') {
            *(buffer_ptr + i) = '\0';
            break;
        }
    }
}

void
update_field(char *attribute, char *field, int max_size,
             unsigned short int new)
{

    int debug = 0;
    char buffer[MAX_BUFFER_SIZE];

    if (new)  {
        printf("Enter %s: ", attribute);
    }
    else {
        printf("Enter %s (%s):\n", attribute, field);
        printf("(Type 'same' all lower case to keep old value): ");
    }

    fgets(buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(buffer);

    printf("\n\n");

    /* Copy input (safely) into given field */
    if (strncmp(buffer, "same", max_size)) {
        strncpy(field, buffer, max_size);
        /* Extra safety -- a terminating null at the memory border */
        *(field + max_size - 1) = '\0';
    }
}

void
edit_address(FILE * fp)
{
    struct address_entry address;
    int index = -1;

    printf("Edit Address\n");
    printf("============\n\n");

    index = get_index("edit");
    read_address(fp, index, &address);

    update_field("First Name", address.fname, FNAME_LENGTH, FALSE);
    update_field("Last Name", address.lname, LNAME_LENGTH, FALSE);
    update_field("Email", address.email, EMAIL_LENGTH, FALSE);
    update_field("Phone", address.phone, PHONE_LENGTH, FALSE);

    update_address(fp, index, &address);
}

int
main(void)
{
    FILE *fp;
    struct address_entry address;
    char choice = '\0';

    fp = open_db("r+");

    system("clear");

    do {
        choice = menu();

        switch (choice) {
        case 'I':
            list_index(fp);
            break;
        case 'D':
            delete(fp);
            break;
        case 'U':
            undelete(fp);
            break;
        case 'N':
            new(&address);
            break;
        case 'E':
            edit_address(fp);
            break;
        case 'Q':
            exit(0);
        default:
            printf("Character '%c' not recognized.\n", choice);
            break;
        }
    } while (TRUE);

    return 0;
}
