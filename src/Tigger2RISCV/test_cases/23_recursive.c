int n;
int putint(int i);
int getint();
int putchar(int i);
int f(int x)
{
	if(x==1)
		return 1;
	if(x==2)
		return 1;
	int a;
	int b;
	a=x-1;
	b=x-2;
	int c;
	c = f(a)+f(b);
	return c;
}
int main()
{
	n=getint();
	int t;
	int xx;
	t=f(n);
	n=putint(t);
	int newline;
	newline = 10;
	n=putchar(newline);
	return t;
}
