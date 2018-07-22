#define MAXVAL 	100

int sp = 0;
double val[MAXVAL];

void push(double op)
{
    if (sp < MAXVAL) {
	val[sp++] = op;
    }
    else {
	printf("error: stack full, can't push %g\n", op);
    }
}

double pop(void)
{
    if (sp >= 0) {
	return val[--sp];
    }
    else {
	printf("error: stack empty\n");
	return 0.0;
    }
}

