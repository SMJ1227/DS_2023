#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

typedef struct ST_INFO {
	int id;
	char name[10];
	int score;
	struct ST_INFO *link;
}ST_INFO;
