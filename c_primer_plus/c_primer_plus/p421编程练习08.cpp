// 编程练习 14.18 巨人航空公司
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAMELEN 41
#define SEATSNUM 12
#define FNAME "p421data.dat"

struct Seat
{
	enum is_rang{NO, YES};
	int num;
	is_rang is_r;
	char fname[NAMELEN];
	char lname[NAMELEN];	
};

int getmenu(void);
int getlet(const char *);
void showEmpty(const Seat *);
void showSeats(const Seat *);
void assign(Seat *);
void D_assign(Seat *);

int main(void)
{
	int choice;
	FILE * fp;
	Seat seats[SEATSNUM];

	

	if (NULL == (fp = fopen(FNAME, "rb")))
	{
		for (int i = 0; i < SEATSNUM; i++)
		{
			seats[i].num = i + 1;
			seats[i].is_r = seats[i].NO;
			strcpy(seats[i].fname, "Nobody");
			strcpy(seats[i].lname, "Nobody");
		}
	}
	else
	{
		fread(seats, sizeof(Seat), SEATSNUM, fp);
		fclose(fp);
	}
	while ((choice = getmenu())&&choice != 'f')
	{
		switch(choice)
		{
		case 'b': showEmpty(seats); break;
		case 'c': showSeats(seats); break;
		case 'd': assign(seats); break;
		case 'e': D_assign(seats); break;
		}
	}
	if (NULL == (fp = fopen(FNAME, "wb")))
	{
		fprintf(stderr, "Can't open file %s\n", FNAME);
		exit(EXIT_FAILURE);
	}

	fwrite(seats, sizeof(Seat), SEATSNUM, fp);
	fclose(fp);
	puts("Done!");

	return 0;
}

int getmenu(void)
{
	puts("To choose a function, enter its letter label:");
	puts("b> Show list of empty seats");
	puts("c> Show alphabetical list of seats");
	puts("d> Assign a customer to a seat assignment");
	puts("e> Delete a seat assignment");
	puts("f> Quit");
	return getlet("bcdef");
}

int getlet(const char * str)
{
	int temp;
	while ((temp = getchar()) && strchr(str, temp) == NULL)  //(temp = getchar())这里外面的括号是必须的, 为什么??????????
	{
		while (getchar() != '\n');
		printf("Error: Please enter one of \"%s\"\n", str);
		puts("Write again:");
	}
	while (getchar()!= '\n');
	return temp;
}

void showEmpty(const Seat * s)
{
	for (int i = 0; i < SEATSNUM; i++)
		if (s[i].is_r != s[i].YES)
			printf("ID: %d ", s[i].num);
	putchar('\n');
}

void showSeats(const Seat * s)
{
	for (int i = 0; i < SEATSNUM; i++)
		if (s[i].is_r == s[i].YES)
			printf("ID: %d Assigned by: %s, %s\n", s[i].num, s[i].fname, s[i].lname);
		else
			printf("Id: %d Empty\n", s[i].num);
}

void assign(Seat * s)
{
	int i, choice, flag = 0;
	printf("ID:");
	while (scanf("%d", &choice) == 1)
	{
		for (i = 0; i < SEATSNUM; i++)
			if (choice == s[i].num && s[i].is_r != s[i].YES)
			{
				s[i].is_r = s[i].YES;
				puts("Fname: ");
				scanf("%s", s[i].fname);
				puts("Lname: ");
				scanf("%s", s[i].lname);
				puts("Assigned!");
				flag = 1;
				break;
			}
			else if (choice == s[i].num && s[i].is_r == s[i].YES)
				puts("已经被定了");
			else if (choice > SEATSNUM)
			{
				puts("Error inputs, write again:");
				while(getchar()!='\n');
			}
			if (flag == 1)
				break;
	}
	while(getchar()!='\n');
}

void D_assign(Seat * s)
{
	int choice;
	int i, flag = 0;
	puts("ID:");
	while(scanf("%d", &choice) == 1)
	{
		for (i = 0; i < SEATSNUM; i++)
			if (choice == s[i].num && s[i].is_r == s[i].YES)
			{
				s[i].is_r = s[i].NO;
				puts("Delete!");
				flag = 1;
				break;
			}
			else if (choice == s[i].num && s[i].is_r != s[i].YES)
				puts("Not assign one can't be deleted.");
			else if (choice > SEATSNUM)
				{
				puts("Error inputs, write again:");
				while(getchar()!='\n');
			}
		if (flag == 1)
			break;
	}
	while (getchar() != '\n');
}