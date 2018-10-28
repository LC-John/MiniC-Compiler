int a;
int b;
int c;
int getint();

int func(int a, int b)
{
	if (a < 0 || a == 0)
		return b;
	int c;
	c = a + b;
	a = a - 1;
	return func(a, c);
}

int main(){
	a = getint();
	b = 0;
	c = func(a, b) + func(a, b);
	return c;
}
