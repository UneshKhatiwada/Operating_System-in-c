#include <stdio.h>
typedef struct
{
    int usn;
    char name[25];
    int m1, m2, m3;
} STD;
void display(FILE *);
int search(FILE *, int);

int main()
{
    int i, n, usn_key, opn;
    FILE *fp;

    printf("How many Records? ");
    scanf("%d", &n);

    fp = fopen("stud.dat", "w");
    for (i = 0; i < n; i++)
    {
        STD s;
        printf("Read the Info for Student %d (usn, name, m1, m2, m3):\n", i + 1);
        scanf("%d%s%d%d%d", &s.usn, s.name, &s.m1, &s.m2, &s.m3);
        fwrite(&s, sizeof(s), 1, fp);
    }
    fclose(fp);

    fp = fopen("stud.dat", "r");
    do
    {
        printf("Press 1 - Display\t2 - Search\t3 - Exit\tYour Option? ");
        scanf("%d", &opn);
        switch (opn)
        {
        case 1:
            printf("\nStudent Records in the File:\n");
            display(fp);
            break;
        case 2:
            printf("Read the USN of the student to be searched: ");
            scanf("%d", &usn_key);
            if (search(fp, usn_key))
            {
                printf("Success! Record found in the file.\n");
            }
            else
            {
                printf("Failure! Record with USN %d not found.\n", usn_key);
            }
            break;
        case 3:
            printf("Exit. Press any key...");
            getchar();
            getchar();
            break;
        default:
            printf("Invalid Option! Try again.\n");
            break;
        }
    } while (opn != 3);

    fclose(fp);
    return 0;
}
void display(FILE *fp)
{
    STD s;
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("%d\t%s\t%d\t%d\t%d\n", s.usn, s.name, s.m1, s.m2, s.m3);
    }
}
int search(FILE *fp, int usn_key)
{
    STD s;
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.usn == usn_key)
            return 1;
    }
    return 0;
}