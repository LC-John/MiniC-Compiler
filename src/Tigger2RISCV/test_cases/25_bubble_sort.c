//sample:input n number, sort them and print them;
int n;
int getint();
int putint(int i);
int putchar(int c);
int a[105];
int blank;
int newline;
int main()
{
	blank=32;
	newline=10;
	n=getint();
	int i;
	int j;
	int t;
	i=0;
	while(i<n)
	{
		a[i]=getint();
		i=i+1;
	}
	i=n-1;
	while(i>0)
	{
		j=0;
		while(j<i)
		{
			if(a[j]>a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
			j=j+1;
		}
		i=i-1;
	}
	i=0;
	while(i<n)
	{
		t=a[i];
		t=putint(t);
		t=putchar(newline);
		i=i+1;
	}
	return 0;
}
