#include <ctype.h>
#define NUMBER 	'0'

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c, d;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
	;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
	return c;
    }
    i = 0;
    // This loop is concise, but it does require one to separate the '-' and any other operator symbol by a space.
    if (c == '-') {
	d = getch();
	if (d == ' ') {
	    return c;
	}
	else {
	    ungetch(d);
	}
    }

    if (isdigit(c)) {
	while (isdigit(s[++i] = c = getch())) {
	    ;
	}
    }
    if (c == '.') {
	while (isdigit(s[++i] = c = getch())) {
	    ;
	}
    }

    s[i] = '\0';
    if (c != EOF) {
	ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

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
