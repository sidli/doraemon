#include<stdio.h>
int a=51;
int a2=51;
static int b=52;
const int c=53;
int m;
int n;
int main()
{
char *s1 = "hello world";
char *s2 = "hello world";
char *s3 = "miao world";
func(s1);
func(s2);
func(s3);
return 0;
}
int func(char *unused)
{
static int f=59;
int d=54;
const int e=55;
int *pe=(int*)&e;
*pe=60;
int *pc=(int*)&c;
//*pc=60;
printf("c:%d e:%d",*pc,*pe);
return 0;
}