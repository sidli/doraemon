/**
*sid is here
**/
#ifndef MAIN
#define MAIN

#include <stdio.h>
#define string char*

#pragma pack(push)
#pragma pack(4)
int main()
{
string message="hello world";
printf(message);
return;
}
#pragma pack(pop)
#endif