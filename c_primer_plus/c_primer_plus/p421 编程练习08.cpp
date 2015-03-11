#include <stdio.h>
#include <stdlib.h>  // exit()
#include <string.h>  // strchr() strcat()
#include <ctype.h>
#define LEN 14  // 姓 和 名 的最大长度
#define SEATS 12  // 座位数
#define EMPTY 0
#define TAKEN 1
#define CONTINUE 1
#define DONE 0
#define FILENAME "p421 编程练习08.dat"

struct planestats
{
	int seat_id;
	int status;
	char last[LEN];
	char first[LEN];
};

int getmenu(void);
	int getlet(const char *);
int openings(const planestats [], int);
void show_emptys(const struct planestats [], int);
	void makelist(const struct planestats [], char *, int);
void list_assign(struct planestats * [], int);
	void sort(struct planestats *[], int);
void delete_seat(struct planestats [], int);
void assign_seat(struct planestats [], int);
void show_seat(const struct planestats [], int);

int main(void)
{
	struct planestats plane[SEATS], *planePtr[SEATS];
	int choice;
	FILE * fp;
	size_t size = sizeof(struct planestats);

	for (int i = 0; i < SEATS; i++)  // 使用指针的原因是以后进行排序并不是排的数据本身, 而是对指针指向数据进行的排序
		planePtr[i] = &plane[i];

	if (NULL == (fp = fopen(FILENAME, "rb")))
		for (int i = 0; i < SEATS; i++)
		{
			plane[i].seat_id = i + 1;
			plane[i].status = EMPTY;
		}
	else
	{
		fread(plane, size, SEATS, fp);
		fclose(fp);
	}

	while ((choice = getmenu()) != 'q')
	{
		switch (choice)
		{
		case 'o': printf("There are %d empty seats, \n", openings(plane, SEATS));break;
		case 'e': show_emptys(plane, SEATS);break;
		case 'l': list_assign(planePtr, SEATS); break;
		case 'a': assign_seat(plane, SEATS); break;
		case 'd': delete_seat(plane, SEATS); break;
		default: puts("Switch trouble!");
		}
	}
	if (NULL == (fp = fopen (FILENAME, "wb")))
		puts ("Can't save data to file.");
	else
	{
		fwrite (plane, size, SEATS, fp);
		fclose (fp);
	}
	puts ("Done!");

	return 0;
}

#define CHOICE 6
int getmenu(void)
{
	const char * descript[CHOICE] = {
		"Show number of empty seats",
		"Show list of empty seats",
		"Show alphabetical list of seat assignments",  // alphabet 字母表, 字母系统 alphabetical 按照字母顺序的
		"Assign a customer to a seat",
		"Delete a seat assignment",
		"Quit"
	};
	const char labels[CHOICE + 1] = "oeladq";  // label 标签 标注 商标
	puts("To choose a function, enter its letter label:");
	for (int i = 0; i < CHOICE; i++)
		printf("%c> %s\n", labels[i], descript[i]);
	return getlet(labels);
}

int getlet(const char * str)
{
	char choice;
	while ((choice = getchar()) && strchr(str, choice) == NULL)
	{
		printf("Please enter a character in list \"%s\":", str);
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	return choice;
}

int openings(const planestats plane[], int seatsNum)
{
	int ct = 0;
	for (int i = 0; i < seatsNum; i++)
		if (plane[i].status == EMPTY)
			ct++;
	return ct;
}

void show_emptys(const struct planestats pl[], int n)
{
	int seat;
	char seating[20 * SEATS];

	if (0 == openings(pl, n))
		puts("All seats are assigned");
	else
	{
		puts("The following seats are available:");
		makelist(pl, seating, EMPTY);
		puts(seating);
	}
}

void makelist(const planestats pl[], char * str, int status)
{
	int seat;
	char temp[LEN];

	str[0] = '\0';
	for (seat = 0; seat < SEATS; seat++)
		if (pl[seat].status == status)
		{
			sprintf(temp, "%d号座", pl[seat].seat_id);
			strcat(str, temp);
		}
}

void list_assign(struct planestats * ps[], int n)
{
	int i;
	if (openings (*ps, n) == SEATS)
		puts("All seats are empty.");
	else
	{
		sort(ps, n);
		for (i = 0; i < SEATS; i++)
			if (ps[i]->status == TAKEN)
				printf("Seat %d: %s, %s\n", ps[i]->seat_id, ps[i]->last, ps[i]->first);
	}
}

void sort(struct planestats * array[], int limit)
{
	int top, search;
	struct planestats * temp;
	for (top = 0; top < limit - 1; top++)
		for (search = top + 1; search < limit; search++)
			if (strcmp(array[search]->last, array[top]->last) < 0)
			{
				temp = array[search];
				array[search] = array[top];
				array[top] = temp;
			}
}

void show_seat(const struct planestats pl[], int n)
{
	int i;
	puts("Seats currently taken:");
	for (i = 0; i < SEATS; i++)
		if (pl[i].status == TAKEN)
			printf ("Seat %d: %s, %s\n", pl[i].seat_id, pl[i].last, pl[i].first);
}

void assign_seat (struct planestats pl[], int n)
{
	char list[20 * SEATS];
	int seat, loop;

	if (openings (pl, n) == 0)
		puts ("All seats are assigned.");
	else
	{
		makelist (pl, list, EMPTY);
		puts ("Which seat do you want? Choose from this list:");
		puts (list);
		do
		{
			while (1 != scanf ("%d", &seat))
			{
				scanf ("%*s");
				puts ("Enter a number from this list:");
				puts (list);
			}
			if (seat < 1 || seat > SEATS ||
				pl[seat - 1].status == TAKEN)
			{
				puts ("Enter a number from this list:");
				puts (list);
				loop = CONTINUE;
			}
			else
				loop = DONE;
		}while (loop == CONTINUE);
		while (getchar () != '\n')
			continue;
		puts ("Enter first name:");
		gets (pl[seat - 1].first);
		puts ("Enter last name:");
		gets (pl[seat - 1].last);
		printf ("%s %s assigned to seat %d.\n",
			pl[seat - 1].first, pl[seat - 1].last, seat);
		puts ("Enter a to accept assignment, c to cancel it.");
		if (getlet ("ac") == 'a')
		{
			pl[seat - 1].status = TAKEN;
			puts ("Passenger assigned to seat.");
		}
		else
			puts ("Passenger not assigned.");
	}
}

void delete_seat (struct planestats pl[], int n)
{
	int seat, loop;
	char list[20 * SEATS];
	if (openings (pl, n) == SEATS)
		puts ("All seats already are empty.");
	else
	{
		show_seat (pl, n);
		makelist (pl, list, TAKEN);
		puts ("Enter the number of the seat to be cancelled:");
		do
		{
			while (scanf ("%d", &seat) != 1)
			{
				scanf ("%*s");
				puts ("Enter a number from this list:");
				puts (list);
			}
			if (seat < 1 || seat > SEATS ||
				pl[seat - 1].status == EMPTY)
			{
				puts ("Enter a number from this list:");
				puts (list);
				loop = CONTINUE;
			}
			else
				loop = DONE;	
		}while (loop == CONTINUE);
		while (getchar () != '\n')
			continue;
		printf ("%s %s to be canceled for seat %d.\n",
			pl[seat - 1].first, pl[seat - 1].last, seat);
		puts ("Enter d to delete assignment, a to abort.");
		if (getlet ("da") == 'd')
		{
			pl[seat - 1].status = EMPTY;
			puts ("Passenger dropped.");
		}
		else 
			puts ("Passenger retained.");
	}
}