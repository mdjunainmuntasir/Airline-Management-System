/*
	Format for the programmer's block
	Description: The Econo-Airlines fleet consists of one plane with a seating
					capacity of 12. It makes one flight daily.
					The aircraft seating is arranged in 6 rows with 2 seats per row. The
					program uses an array of 12 structures. Each structure holds a seat
					identification number, a marker that indicates whether the seat is
					assigned, the last name of the seat holder, and the first name of the seat holder

	Programmer name: Md Junain Muntasir

	Date: 7 April 2024
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SEATS 12

struct seat
{
	int seatId;
	int assigned;
	char lastName[50];
	char firstName[50];
};

void explainProg(void);
void seatsFromFile(struct seat seatInfo[]);
void displayMenu(struct seat seatInfo[]);
void disAllSeats(struct seat seatInfo[]);
void disEmptSeats(struct seat seatInfo[]);
void disAssignSeats(struct seat seatInfo[]);
void assignSeat(struct seat seatInfo[]);
void delOneSeat(struct seat seatInfo[]);
void delAllSeats(struct seat seatInfo[]);
void saveSeatsInFile(struct seat seatInfo[]);

int main()
{
	struct seat seatInfo[MAX_SEATS];

    explainProg();

	seatsFromFile(seatInfo);

	displayMenu(seatInfo);

	return 0;
}

void explainProg(void)
{
    printf("This programme will first show a menu that has included a lot of option");
    printf("The user will choose a suitable option. Every option has each funtion");
    printf("Each function has perfomed different information.");
    printf("Even the programme is also able to record all the previous data.");
    printf("This programme is a whole system how a airline company's software runs\n\n.");
}

void seatsFromFile(struct seat seatInfo[])
{
	FILE* folder = fopen("AirReserved", "r");
	if (folder == NULL)
	{
		printf("File not found.Creating new file named AirReserved.\n");

		folder = fopen("AirReserved", "w");

		if (folder == NULL)
		{
			printf("\n File was not created. Exiting the program!\n");
			exit(1);
		}
		else
		{
			printf("\n New folder AirReserved created successfully\n");

		}
	}
	else
	{
		printf("\nFile named AirReserve exists and will be reading and storing the data to and from the file.\n");
		fread(seatInfo, sizeof(struct seat), MAX_SEATS, folder);
		fclose(folder);

	}
	return;
}
void displayMenu(struct seat seatInfo[])
{
    char choice;

    printf("\n\Econo-Flight Airline Reservation Program\n");
    printf("\nA. Display ALL seat assignments (including Empty).\n");
    printf("\nB. Show ONLY a list of empty seats and show total of empty seats.\n");
    printf("\nC. Show ONLY the assigned seats with name of person and total assigned.\n");
    printf("\nD. Assign the customer to an empty seat.\n");
    printf("\nE. Delete ONE seat assignment.\n");
    printf("\nF. Delete ALL seat assignments.\n");
    printf("\nQ. Save data to the file and quit program.\n");

    do
    {
        printf("\nEnter your choice from the options above: ");
        scanf(" %c", &choice);
        choice = toupper(choice);

        switch (choice)
        {
        case 'A':
            disAllSeats(&seatInfo);
            break;
        case 'B':
            disEmptSeats(&seatInfo);
            break;
        case 'C':
            disAssignSeats(&seatInfo);
            break;
        case 'D':
            assignSeat(&seatInfo);
            break;
        case 'E':
            delOneSeat(&seatInfo);
            break;
        case 'F':
            delAllSeats(&seatInfo);
            break;
        case 'Q':
            saveSeatsInFile(&seatInfo);
            break;
        default:
            printf("\nInvalid choice. Please enter the accurate choice.\n");
        }
    } while (choice != 'Q');

    return;
}

void disAllSeats(struct seat seatInfo[])
{
    char seatid[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    char assigned[4];

    printf("\nSeat assignments of the airline:\n\n");
    printf("\N%-10s%-15s%-12s%-10s\n", "Seat ID", "First Name", "Last Name", "Assigned");

    for (int column = 0; column < 2; column++)
    {
        for (int row = 0; row < 6; row++)
        {
            int index = row * 2 + column;

            if (seatInfo[index].assigned)
            {
                strcpy(assigned, "Yes");
            }
            else
            {
                strcpy(assigned, "No");
            }

            printf("\n%c%-9d%-16s%-14s%s\n", seatid[row], column + 1, seatInfo[index].firstName, seatInfo[index].lastName, assigned);
        }
    }

    return;
}

void disEmptSeats(struct seat seatInfo[])
{
    int count = 0;
    int choice = 0;
    char seatletter[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    printf("\nEmpty seats in the Airline:\n");

    printf("\n%-15s%-15s\n", "Seat ID", "Status");

    for (int row = 0; row < 6; row++)
    {
        for (int column = 0; column < 2; column++)
        {
            int index = row * 2 + column;
            if (seatInfo[index].assigned == 0)
            {
                printf("\n\t%c%d  Empty\n", seatletter[row], column + 1);
                count++;
            }
        }
    }
    printf("\nTotal empty seats in the airline: %d\n", count);

    return;
}

void disAssignSeats(struct seat seatInfo[])
{
    int assignCount = 0;
    char seatId[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    printf("\nAssigned seats in the Airline:\n");

    printf("\n%-15s%-18s%-20s\n", "Seat ID", "First Name", "Last Name");

    for (int row = 0; row < 6; row++)
    {
        for (int column = 0; column < 2; column++)
        {
            int index = row * 2 + column;

            if (seatInfo[index].assigned != 0)
            {
                printf("\n%c%-10d\t%-18s%-20s\n", seatId[row], column + 1, seatInfo[index].firstName, seatInfo[index].lastName);
                assignCount++;
            }
        }
    }
    printf("\nTotal assigned seats in the airline: %d\n", assignCount);

    return;
}

void assignSeat(struct seat seatInfo[])
{
    char seatLetter;
    int seatNumber;
    int index;
    int choice = 0;

    do
    {
        printf("\n\t\t\tEnter the seat row (A-F): ");
        scanf(" %c", &seatLetter);
        seatLetter = toupper(seatLetter);

        printf("\n\t\t\tEnter the seat column (1-2): ");
        scanf("%d", &seatNumber);

        if (seatLetter < 'A' || seatLetter > 'F' || seatNumber < 1 || seatNumber > 2)
        {
            printf("\n\t\t\tInvalid seat selection.Please enter the correct inputs(A-F and 1-2).\n");
            return;
        }

        index = (seatLetter - 'A') * 2 + seatNumber - 1;

        if (seatInfo[index].assigned)
        {
            printf("\nThis seat is already assigned to %s %s.\n", seatInfo[index].firstName, seatInfo[index].lastName);
        }
        else {
            printf("\nEnter passenger's first name: ");
            scanf(" ");
            gets(seatInfo[index].firstName);

            printf("\nEnter passenger's last name: ");
            gets(seatInfo[index].lastName);

            seatInfo[index].assigned = 1;
            printf("\n\Seat %c%d assigned to %s %s successfully.\n", seatLetter, seatNumber + 1, seatInfo[index].firstName, seatInfo[index].lastName);
        }
        printf("\nDo you want to assign another seat?\n 0 for No\n 1 for Yes:\n ");
        scanf(" %d", &choice);

    } while (choice == 1);
    return;
}

void delOneSeat(struct seat seatInfo[])
{
    char rowLetter;
    int columnNum;
    int choice = 0;

    do
    {
        printf("\nEnter seat number to delete assignment: ");
        scanf(" %c%d", &rowLetter, &columnNum);
        rowLetter = toupper(rowLetter);
        ;

        int index = (rowLetter - 'A') * 2 + columnNum - 1;

        if (index < 0 || index >= MAX_SEATS)
        {
            printf("\nInvalid seat number.\n");
            return;
        }
        else if (!seatInfo[index].assigned)
        {
            printf("\nSeat %c%d is already empty.\n", rowLetter, columnNum + 1);
        }
        else
        {
            seatInfo[index].assigned = 0;
            seatInfo[index].firstName[0] = '\0';
            seatInfo[index].lastName[0] = '\0';
            printf("\nSeat Reservation for seat %c%d deleted.\n", rowLetter, columnNum + 1);
        }
        printf("\nDo you want to delete another seat? \n 0 for No \n 1 for Yes: ");
        scanf(" %d", &choice);

    } while (choice == 1);

    return;
}

void delAllSeats(struct seat seatInfo[])
{
    printf("\nDeleting ALL Assigned Seats:\n");

    for (int index = 0; index < MAX_SEATS; index++)
    {
        seatInfo[index].assigned = 0;
        seatInfo[index].firstName[0] = '\0';
        seatInfo[index].lastName[0] = '\0';
    }
    printf("\nAll the reserved seats are deleted.\n");

    return;
}

void saveSeatsInFile(struct seat seatinfo[])
{
    FILE* folder = fopen("AirReserve", "w");

    if (folder == NULL)
    {
        printf("\nFailed to save data to the file.\n");
        return;
    }

    fwrite(seatinfo, sizeof(struct seat), MAX_SEATS, folder);
    fclose(folder);

    printf("\nData saved successfully.\n");

    printf("\nExiting the program!");

    return;
}
