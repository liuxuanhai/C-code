// 巨人航空公司的座位预定程序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN        14   // 姓 和 名的长度 
#define SEATS      12
#define EMPTY      0
#define TAKEN      1
#define CONTINUE   1
#define DONE       0

struct planestats {     // stats 统计
	int seat_id;
	int status;
	char last[LEN];
	char first[LEN];
};

int getmenu (void);                                      // 列出选项, 返回getlet();
	int getlet (const char *);                               // 返回用户输入的参数字符串中的一个字符
int openings (const planestats [], int);                 // 遍历结构数组, 返回空坐个数
void show_empties (const struct planestats [], int);     // 输出空座位编号
	void makelist (const struct planestats [], char *, int); // 将参数1结构数组中参数3状态的座位编号以字符串的形式加到参数二指向的数组中
void list_assign (struct planestats *[], int);           // 把被定了的座位输出
	void sort (struct planestats *[], int);					// 对结构的编号进行降序排列
void delete_seat (struct planestats [], int);            // 删除被定的座位
void assign_seat (struct planestats [], int);            // 定座位
void show_seat (const struct planestats [], int);



int main (void)
{
	struct planestats plane_1[SEATS], * ps[SEATS];
	int choice;
	int i;
	FILE * fp;
	size_t size = sizeof (struct planestats);

	for (i = 0; i < SEATS; i++)
		ps[i] = &plane_1[i];
	if (NULL == (fp = fopen ("p421_8air.dat", "rb")))
		for (i = 0; i < SEATS; i++)
		{
			plane_1[i].status = EMPTY;
			plane_1[i].seat_id = i + 1;
		}
	else
	{
		fread (plane_1, size, SEATS, fp);
		fclose (fp);
	}
	while ('q' != (choice = getmenu ()))
	{
		switch (choice)
		{
		case 'o' : printf ("There are %d empty seats.\n",
					   openings (plane_1, SEATS));
			break;
		case 'e' : show_empties (plane_1, SEATS);
			break;
		case 'l' : list_assign (ps, SEATS);
			break;
		case 'a' : assign_seat (plane_1, SEATS);
			break;
		case 'd' : delete_seat (plane_1, SEATS);
			break;
		default : puts ("Switch trouble!");
		}
	}
	if (NULL == (fp = fopen ("p421_8air.dat", "wb")))
		puts ("Can't save data to file.");
	else
	{
		fwrite (plane_1, size, SEATS, fp);
		fclose (fp);
	}
	puts ("Done!");

	return 0;
}

#define CHOICES 6
int getmenu (void)
{
	const char * descript[CHOICES] = {
		"Show number of empty seats",
		"Show list of empty seats",
		"Show alphabetical list of seat assignments",
		"Assign a customer to a seat",
		"Delete a seat assignment",
		"Quit"
	};
	const char labels[CHOICES + 1] = "oeladq";
							  // +1 是为了给'\0'
	int i;                     

	puts ("To choose a fuction, enter its letter label");
	                          // label 标签
	for (i = 0; i < CHOICES; i++)
		printf ("%c) %s\n", labels[i], descript[i]);
	return getlet(labels);
}

int getlet (const char * s)
{
	char c;
	
	c = getchar ();
	while (NULL == strchr (s, c))
	{
		printf ("Enter a character in the list %s\n", s);
		while (getchar () != '\n')
			continue;
		c = getchar ();
	}
	while (getchar() != '\n')
		continue;

	return c;
}

int openings (const struct planestats pl[], int n)
{
	int count = 0;
	int seat;
	
	for (seat = 0; seat < n; seat++)
		if (pl[seat].status == EMPTY)
			count++;
	return count;
}

void show_empties (const struct planestats pl[], int n)
{
	int seat;
	char seating[20 * SEATS];

	if (0 == (openings (pl, n)))
		puts ("All seats are assigned");
	else
	{
		puts ("The following seats are available:");
		makelist (pl, seating, EMPTY);
		puts (seating);
	}
}

void makelist (const struct planestats pl[], char * str, int kind)
{
	int seat;
	char temp[LEN];

	str[0] = '\0';            // 因为strcat(a, b);是用b的内容替换掉第一次遇见'\0'的地方
	for (seat = 0; seat < SEATS; seat++)
		if (pl[seat].status == kind)
		{
			sprintf (temp, "%d号座.", pl[seat].seat_id); 
							 // 将int变成char 也可以用itoa()函数
			strcat (str, temp);
		}
}

void list_assign (struct planestats * ps[], int n)
{
	int i;
	if (openings (*ps, n) == SEATS)
		puts ("All seats are empty.");
	else
	{
		sort (ps, n);
		for (i = 0; i < SEATS; i++)
			if (ps[i]->status == TAKEN)
				printf ("Seat %d: %s, %s\n",
				ps[i]->seat_id, ps[i]->last, ps[i]->first);
	}
}

void show_seat(const struct planestats pl[], int n) 
{ 
     int i; 

     puts("Seats currently taken:"); 
     for (i = 0; i < SEATS; i++) 
          if (pl[i].status == TAKEN) 
              printf("Seat %d: %s, %s\n", pl[i].seat_id, 
                   pl[i].last, pl[i].first); 
} 

void sort (struct planestats * array[], int limit)
{
	int top, search;
	struct planestats * temp;

	for (top = 0; top < limit - 1; top++)
		for (search = top + 1; search < limit; search++)
			if (strcmp (array[search]->last, array[top]->last) < 0)
			{
				temp = array[search];
				array[search] = array[top];
				array[top] = temp;
			}
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