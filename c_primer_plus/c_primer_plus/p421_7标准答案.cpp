// 实现对文件内容的删除和修改
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  10
#define CONTINUE 0
#define DONE     1
#define YES      1
#define NO       0
struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
	int del;
};

int getlet (const char * s);       // 对删除和修改的选择
	// 返回输入字符的int值
int getbook (struct book * pb);
void update (struct book * item);

int main (void)
{
	struct book library[MAXBKS];   // 书结构
	int count = 0;                 // 书读取索引
	int deleted = 0;               // 被标记删除的书的个数
	int index, open;
	int filecount;                 // 未被标示删除的书的个数
	FILE * pbooks;                 // 指向被打开的文件
	int size = sizeof (struct book);

	// 打开文件
	if (NULL != (pbooks = fopen ("p421_7book.dat", "r")))
	{
		// 读取文件
		while (count < MAXBKS && 1 == fread (&library[count], size, 1, pbooks))
		{
			// 输出文件
			if (0 == count)
				puts ("Current contents of book.dat:");
			printf ("%s by %s: $%.2f\n", library[count].title,
				library[count].author, library[count].value);
			// 标记删除或直接更改文件
			printf ("Do you wish to change or delete this entry?<y / n>");
			if ('y' == getlet("yn"))
			{
				puts ("Enter c go change, d to delete entry : ");
				if  ('d' == getlet ("cd"))
				{
					library[count].del = YES;
					deleted++;
					puts ("Entry maked for deletion.");
				}
				else
					update (&library[count]);
			}
			// 准备读取下一内容
			count++;
		}
		// 关闭文件
		fclose (pbooks);
	}
	filecount = count - deleted; // 除去删除的还有几个
	// 删除之前内容已经满了 提示不能写内容了
	if (filecount == MAXBKS)
	{
		fputs ("The book.dat file is full.", stderr);
		exit (2);
	}
	// 添加书
	puts ("Please add new book title.");
	puts ("Press [Enter] at the start of a line to stop.");
	open = 0;
	// 添加之前先把之前标记要删除的删除了
	while (filecount < MAXBKS)  
	{
		// 如果有删除标记的话
		if (filecount < count)  // 正好循环到没有删除标记的时候条件不成立
		{
			// 寻找带有删除标记的文件
			while (NO == library[open].del)
				open++;
			// 用新内容代替要删除的内容
			if (DONE == getbook (&library[open]))
				break;
		}
		// 如果实际内容到了结尾
		else if (getbook (&library[filecount]) == DONE)
			break;

		filecount++;
		if (filecount < MAXBKS)
			puts ("Enter the next book title.");
	}
	puts("Here is the list of your books:"); 

      for (index = 0; index < filecount; index++) 

           if (library[index].del == NO) 

              printf("%s by %s: $%.2f\n",library[index].title, 

                   library[index].author, library[index].value); 

      if ((pbooks = fopen("p421_7book.dat", "w")) == NULL) 

      { 

           fputs("Can't open book.dat file for output\n",stderr); 

           exit(1); 

      } 

      for (index = 0; index < filecount; index++) 

           if (library[index].del == NO) 

              fwrite(&library[index], size, 1, pbooks); 

      fclose(pbooks); 

      puts("Done!"); 
	

	return 0;
}

int getlet (const char * s)
{
	char c;

	c = getchar ();
	while (NULL == strchr (s, c))
	{
		printf ("Enter a character in the list %s\n", s);
		while ('\n' != getchar())
			continue;
		c = getchar ();
	}
	while ('\n' != getchar ())
		continue;

	return c;
}

void update (struct book * item)
{
	struct book copy;
	char c;

	copy = * item;
	puts ("Enter the letter that indicates your choice:");
							  // indicates 指示 象征
	puts ("t) modify title      a) modify author");
							  // modify 改变
	puts ("v) modify value      s) qiut, saving changes");
	puts ("q) qiut, ignore changes");
	while ('s' != (c = getlet ("tavsq")) && 'q' != c)
	{
		switch ( c )
		{
			case 't' : puts ("Enter new title: ");
					   gets (copy.title);
					   break;
			case 'a' : puts ("Enter new author: ");
					   gets (copy.author);
				       break;
			case 'v' : puts ("Enter new value: ");
					   while (1 != scanf ("%f", &copy.value))
					   {
						   puts ("Enter a numeric value:");
						   scanf ("%*s");
					   }
				       while ('\n' != getchar ())
					    	continue;
				       break;
			default :  break;
		}
		puts ("Enter the letter that indicates your choice:");
							  // indicates 指示 象征
		puts ("t) modify title      a) modify author");
							  // modify 改变
		puts ("v) modify value      s) qiut, saving changes");
		puts ("q) qiut, ignore changes");
	}
	if ('s' == c)
		*item = copy;
}

int getbook (struct book * pb)
{
	int status = CONTINUE;  // 现状
	if (gets (pb->title) == NULL || pb->title[0] == '\0') 
	// 1.这个是用来判断用户是否输入空行来进行跳出判断的 
	// 2.gets();读入'\n'并用'\0'替代它
		status = DONE;
	else
	{
		printf ("Now enter the author: "); 
        gets (pb->author); 
		printf ("Now enter the value: "); 
		while (scanf("%f", &pb->value ) != 1) 
        { 
			puts("Please use numeric input"); 
            scanf("%*s"); 
		} 
        while (getchar() != '\n') 
			continue; /*clear input line */
		pb->del = NO;
	}
	return status;
}