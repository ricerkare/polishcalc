#include <math.h>
#include <stdio.h>
#include <stdlib.h> 	/* for atof() */
#include "pushpop.h"
#include "getop.h"
#define MAXOP 	100	/* max size of operand or operator */
#define NUMBER	'0' 	/* signal that a number was found */

void print_top(void);
void duplicate(void);
void swap_top(void);
void print_stack(void);

/* reverse Polish calculator */
int main()
{
    int type, ignore_newline = 0;
    double op1, op2, top;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
	switch (type) {
	case NUMBER:
	    push(atof(s));
	    break;
	case '+' :
	    push(pop() + pop());
	    break;
	case '*':
	    push(pop() * pop());
	    break;
	case '-' :
	    op2 = pop();
	    push(pop() - op2);
	    break;
	case '/':
	    op2 = pop();
	    if (op2 != 0.0) {
		push(pop() / op2);
	    }
	    else {
		printf("error: zero divisor\n");
	    }
	    break;
	case '%':
	    op2 = pop();
	    if (op2 != 0.0) {
		push(fmod(pop(), op2));
	    }
	    else {
		printf("error: modulo zero\n");
	    }
	    break;
	case '?':
	    print_top();
	    ignore_newline = 1;
	    break;
	case '#':
	    duplicate();
	    ignore_newline = 1;
	    break;
	case '~':
	    swap_top();
	    ignore_newline = 1;
	    break;
	case '$':
	    print_stack();
	    ignore_newline = 1;
	    break;
	case '\n':
	    if (ignore_newline) {
		ignore_newline = 0;
	    }
	    else {
		printf("\t%.8g\n", pop());
	    }
	    break;
	default:
	    printf("error: unknown command %s\n", s);
	    break;
	}
    }
    return 0;
}

void print_top() {
    if (sp > 0) {
	printf("\t%g\n", val[sp - 1]);
    }
    else {
	printf("error: stack is empty\n");
    }
}

void duplicate() {
    if (sp > 0) {
	if (sp < MAXVAL) {
	    push(val[sp - 1]);
	}
	else {
	    printf("error: stack is full\n");
	}
    }
    else {
	printf("error: stack is empty\n");
    }
}

void swap_top() {
    if (sp > 1) {
	double op1 = pop();
	double op2 = pop();
	push(op1);
	push(op2);
    }
    else {
	printf("error: stack has fewer than two elements");
    }
}

void print_stack() {
    if (sp > 0) {
	printf("stack:\n");
	for (int i = sp-1; i >= 0; i--) {
	    printf("\t%g\n", val[i]);
	}
    }
    else {
	printf("error: stack is empty\n");
    }
}
