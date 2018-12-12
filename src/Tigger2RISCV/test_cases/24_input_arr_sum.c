//sample:input n numbers,then print the sum of them;
int getint();
int putint(int x);
int putchar(int i);
int n;
int a[10];
int main()
{
	n = getint();
	if (n > 10) 
		return 1;
	int s;
	int i;
	i = 0;
	s = i;
	while (i < n) { 
	a[i] = getint();
	s = s + a[i]; 
	i=i+1;
	} 
	n=putint(s);
	int newline;
	newline = 10;
	n=putchar(newline);
	return s;
}
