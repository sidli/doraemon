#ifndef PRINT_PRETTY
#define PRINT_PRETTY

#include <stdio.h>
#include <string.h>
static char *firstline="############################################################\n";
static char *secondline="##****************                        ****************##\n";
int print_pretty(const char *regard)
{
printf(firstline);
printf(secondline);
int len = strlen(regard);
int spos = (80-len)/2-10;
printf("##********");
for(int i=0;i<spos-10;i++) printf(" ");
printf(regard);
for(int i=0;i<spos-10;i++) printf(" ");
printf(len/2?" ":"");
printf("********##\n");
printf(secondline);
printf(firstline);
return 0;
}
#endif