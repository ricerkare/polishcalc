/* There is one bug in the previous solutions. In the function used to 
   duplicate the top element, people are not checking whether there is sufficient 
   space for another element to be inserted in the stack. I've made the necessary changes.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER 0
#define MAXVAL 100
#define BUFSIZE 100

int getop(char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void view_stack(void);
void show_top(void);
void swap(void);
void duplicate(void);
void clear_stack(void);

int bufp = 0;
char buf[BUFSIZE];
int sp = 0;
double val[MAXVAL];


int main()
{
    int type, ignore_newline = 0;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
	switch(type) {
	case NUMBER:
	    push(atof(s));
	    break;
	case '+':
	    push(pop() + pop());
	    break;
	case '*':
	    push(pop() * pop());
	    break;
	case '-':
	    op2 = pop();
	    push(pop() - op2);
	    break;
	case '/':
	    op2 = pop();
	    if(op2 != 0.0)
		push(pop() / op2);
	    else
		printf("error: zero divisor\n");
	    break;
	case '%':
	    op2 = pop();
	    if(op2 != 0.0)
		push(fmod(pop(), op2));
	    else
		printf("error: modulo zero\n");
	    break;
	case '?': // show top item on stack without popping
	    show_top();
	    ignore_newline = 1;
	    break;
	case '~': // swap top two elements of the stack
	    swap();
	    ignore_newline = 1;
	    break;
	case '#': // duplicate the top element
	    duplicate();
	    ignore_newline = 1;
	    break;
	case '!': // clear_stack
	    clear_stack();
	    ignore_newline = 1;
	    break;
	case '$':
	    view_stack();
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

void push(double f)
{
    if (sp < MAXVAL) {
	val[sp++] = f;
    }
    else {
	printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void)
{
    if (sp > 0) {
	return val[--sp];
    }
    else {
	printf("error: stack is empty\n");
	return 0.0;
    }
}

int getch(void)
{
    if (bufp > 0) {
	return buf[--bufp];
    }
    else {
	return getchar();
    }
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
	printf("ungetch: too many characters\n");
    }
    else {
	buf[bufp++] = c;
    }
}

int getop(char *s)
{
    int i, c, d;
    while ((s[0] = c = getch()) == ' ' || c == '\t') {
	;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
	return c;
    }
    if (c == '-') {
	d = getch();
	if(d == ' ') {
	    return c;
	}
	else {
	    ungetch(d);
	}
    }
    i = 0;
    if(isdigit(c) || c == '-') {
	while(isdigit(s[++i] = c = getch())) {
	    ;
	}
    }
    if(c == '.') {
	while(isdigit(s[++i] = c = getch()));
    }
    s[i] = '\0';
    if(c != EOF) {
	ungetch(c);
    }
    return NUMBER;
}

void view_stack(void)
{
    int i;
    printf("\nstack:\n");
    for(i = sp - 1; i >= 0; i--) {
	printf("%lf\n", val[i]);
    }
}

void show_top(void)
{
    if (sp > 0) {
	printf("\t%.8g\n", val[sp-1]);
    }
    else {
	printf("error: stack is empty\n");
    }
	    
}

void swap(void)
{
    double temp;
    if(sp < 1)
	printf("error: stack has less than 2 elements, can't swap\n");
    else
    {
	temp = val[sp - 1];
	val[sp - 1] = val[sp - 2];
	val[sp - 2] = temp; 
    }
}

void duplicate(void)
{
    if(sp > MAXVAL - 1)
	printf("error: stack is full, can't duplicate\n");
    else
    {
	double temp = pop();
	push(temp);
	push(temp);
    }
}

void clear_stack(void)
{
    sp = 0;
}
