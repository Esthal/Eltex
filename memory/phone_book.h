#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

struct test{
	char name[51];
	char last_name[51];
	char phone[21];
};

void print_command(void);
void view(struct test *);
void delete(struct test **, int);
void add(struct test **);
void find(struct test *);