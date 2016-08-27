#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include  <chrono>
#include <ratio>
//#include <ctime>
#include<time.h>
#include <Windows.h>
//#include <WinBase.h>


typedef struct abb
{
	unsigned long long  tv_sec;
	unsigned long long  tv_usec;
}abb;
 abb Q;
 void initgettimeofday(abb *Q)
 {
	Q->tv_sec = 0;
	Q->tv_usec = 0;
 }

void gettimeofday(abb *Q, void* timezone);
int _tmain(int argc, _TCHAR* argvp[])
{
	initgettimeofday(&Q);
	double time1, time2;
	double delta;
	 long i = 0;
	gettimeofday(&Q,NULL);
	time1 =Q.tv_sec + (Q.tv_usec / 1000000.0);
	for (i = 0; i < 5000; i++);
//	Sleep(1);

	gettimeofday(&Q, NULL);
	time2 = Q.tv_sec + (Q.tv_usec / 1000000.0);
	delta = (time2 - time1)*1e6 ;
	printf("time1: %f usec\n", time1);
	printf("time2: %f usec\n", time2);
	printf("time: %f usec\n",delta);
	printf("finish\n");

	return 0;

}


void gettimeofday(abb *Q, void* timezone)
{
//	struct timeval *tv;
	SYSTEMTIME sysTime;
	FILETIME time;
	double timed;
	GetSystemTime(&sysTime);
	SystemTimeToFileTime(&sysTime, &time);

	timed = ((time.dwHighDateTime *4294967296e-7) -11644473600.0) + (time.dwLowDateTime * 1e-7);
	Q->tv_sec = ( long)timed;
	printf("\ndw: %llf\n", time.dwHighDateTime);
	Q->tv_usec = ( long)((timed - Q->tv_sec)*1e6);
}