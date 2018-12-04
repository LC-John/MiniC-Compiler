int main(){
	return 0;
}


int a;
int main(){
	a=10;
	return 0;
}


int a;
int b;
int main(){
	a=10;
	int c;
	c=10;
	return 0;
}


int a[10];
int main(){
	return 0;
}


int a;
int func(int p){
	p = p - 1;
	return p;
}
int main(){
	int b;
	a = 10;
	b = func(a);
	return b;
}


int a;
int b;

int main(){
	a=10;
	b=20;
	int c;
	c = a + b;
	return c;
}


int a;
int b;
int main(){
	a = 10;
	b = 3;
	int c;
	c = a % b;
	return c;
}


int a;

int main(){
	a=10;
	return a;
}


int a[10];
int main(){
	a[0]=1;
	return 0;
}


int a;

int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	return 0;
}


int a;
int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int main(){
	b=0;
	a=3;
	while(a>0){	
		b = b+a;
		a = a-1;
	}
	return b;
}	


int getint();
int main(){
	int a;
	a = getint();
	return a;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a && b ) {
		return 1;
	}
	else {
		return 0;
	}
}


int a;
int b;
int getint();
int main() {
	a = getint();
	b = getint();
	if ( a || b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a == b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a != b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a < b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int c;
int getint();
int main(){
	a = getint();
	b = getint();
	c = getint();
	int d;
	d = a+b*c;
	return d;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	int c;
	c = -(a + b);
	return c;
}


int getint();
int a[5];
int main(){
	a[0] = getint();
	a[1] = getint();
	a[2] = getint();
	a[3] = getint();
	a[4] = getint();
	int cnt;
	cnt = 4;
	int sum;
	sum = 0;
	while( cnt > 1 ){
		sum = sum + a[cnt];
		cnt = cnt - 1;
	}
	return sum;
}


int putint(int i);
int getint();
int n;
int fib(int p){
	int a;
	int b;
	int c;
	a = 0;
	b = 1;
	if ( p == 0 ){
		return 0;
	}
	if ( p == 1 ){
		return 1;
	}
	while ( p > 1 ){
		c = a + b;
		a = b;
		b = c;
		p = p - 1;
	}
	return c;
}
int main(){
	n = getint();
	int res;
	res = fib( n );
	return res;
}


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


//sample:input n number, sort them and print them;
   int n;
   int getint();
   int putint(int i);
   int putchar(int c);
   int main()
   {
      int a0;
      int a1;
      int a2;
      int a3;
      int a4;
      int a5;
      int a6;
      int a7;
      int a8;
      int a9;
      int a10;
      int a11;
      int a12;
      int a13;
      int a14;
      int a15;
      int a16;
      int a17;
      int a18;
      int a19;
      int a20;
      int a21;
      int a22;
      int a23;
      int a24;
      int a25;
      int b;
      b = getint();
      while(b == 5){
          b = b + 1;
      }
      a0=0;
      a1=a0+1;
      a2=a1+1;
      a3=a2+1;
      a4=a3+1;
      a5=a4+1;
      a6=a5+1;
      a7=a6+1;
      a8=a7+1;
      a9=a8+1;
      a10=a9+1;
      a11=a10+1;
      a12=a11+1;
      a13=a12+1;
      a14=a13+1;
      a15=a14+1;
      a16=a15+1;
      a17=a16+1;
      a18=a17+1;
      a19=a18+1;
      a20=a19+1;
      a21=a20+1;
      a22=a21+1;
      a23=a22+1;
      a24=a23+1;
      a25=a24+1;
      int t;
      t=putint(a0);t=putint(a1);t=putint(a2);t=putint(a3);
      t=putint(a4);t=putint(a5);t=putint(a6);t=putint(a7);
      t=putint(a8);t=putint(a9);t=putint(a10);t=putint(a11);
      t=putint(a12);t=putint(a13);t=putint(a14);t=putint(a15);
      t=putint(a16);t=putint(a17);t=putint(a18);t=putint(a19);
      t=putint(a20);t=putint(a21);t=putint(a22);t=putint(a23);
      t=putint(a24);t=putint(a25);
      int newline;
      newline = 10;
      t=putchar(newline);
      t=putint(b);
      t=putchar(newline);
      return a25;
   }


int main(){
	return 0;
}


int a;
int main(){
	a=10;
	return 0;
}


int a;
int b;
int main(){
	a=10;
	int c;
	c=10;
	return 0;
}


int a[10];
int main(){
	return 0;
}


int a;
int func(int p){
	p = p - 1;
	return p;
}
int main(){
	int b;
	a = 10;
	b = func(a);
	return b;
}


int a;
int b;

int main(){
	a=10;
	b=20;
	int c;
	c = a + b;
	return c;
}


int a;
int b;
int main(){
	a = 10;
	b = 3;
	int c;
	c = a % b;
	return c;
}


int a;

int main(){
	a=10;
	return a;
}


int a[10];
int main(){
	a[0]=1;
	return 0;
}


int a;

int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	return 0;
}


int a;
int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int main(){
	b=0;
	a=3;
	while(a>0){	
		b = b+a;
		a = a-1;
	}
	return b;
}	


int getint();
int main(){
	int a;
	a = getint();
	return a;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a && b ) {
		return 1;
	}
	else {
		return 0;
	}
}


int a;
int b;
int getint();
int main() {
	a = getint();
	b = getint();
	if ( a || b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a == b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a != b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a < b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int c;
int getint();
int main(){
	a = getint();
	b = getint();
	c = getint();
	int d;
	d = a+b*c;
	return d;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	int c;
	c = -(a + b);
	return c;
}


int getint();
int a[5];
int main(){
	a[0] = getint();
	a[1] = getint();
	a[2] = getint();
	a[3] = getint();
	a[4] = getint();
	int cnt;
	cnt = 4;
	int sum;
	sum = 0;
	while( cnt > 1 ){
		sum = sum + a[cnt];
		cnt = cnt - 1;
	}
	return sum;
}


int putint(int i);
int getint();
int n;
int fib(int p){
	int a;
	int b;
	int c;
	a = 0;
	b = 1;
	if ( p == 0 ){
		return 0;
	}
	if ( p == 1 ){
		return 1;
	}
	while ( p > 1 ){
		c = a + b;
		a = b;
		b = c;
		p = p - 1;
	}
	return c;
}
int main(){
	n = getint();
	int res;
	res = fib( n );
	return res;
}


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


//sample:input n number, sort them and print them;
   int n;
   int getint();
   int putint(int i);
   int putchar(int c);
   int main()
   {
      int a0;
      int a1;
      int a2;
      int a3;
      int a4;
      int a5;
      int a6;
      int a7;
      int a8;
      int a9;
      int a10;
      int a11;
      int a12;
      int a13;
      int a14;
      int a15;
      int a16;
      int a17;
      int a18;
      int a19;
      int a20;
      int a21;
      int a22;
      int a23;
      int a24;
      int a25;
      int b;
      b = getint();
      while(b == 5){
          b = b + 1;
      }
      a0=0;
      a1=a0+1;
      a2=a1+1;
      a3=a2+1;
      a4=a3+1;
      a5=a4+1;
      a6=a5+1;
      a7=a6+1;
      a8=a7+1;
      a9=a8+1;
      a10=a9+1;
      a11=a10+1;
      a12=a11+1;
      a13=a12+1;
      a14=a13+1;
      a15=a14+1;
      a16=a15+1;
      a17=a16+1;
      a18=a17+1;
      a19=a18+1;
      a20=a19+1;
      a21=a20+1;
      a22=a21+1;
      a23=a22+1;
      a24=a23+1;
      a25=a24+1;
      int t;
      t=putint(a0);t=putint(a1);t=putint(a2);t=putint(a3);
      t=putint(a4);t=putint(a5);t=putint(a6);t=putint(a7);
      t=putint(a8);t=putint(a9);t=putint(a10);t=putint(a11);
      t=putint(a12);t=putint(a13);t=putint(a14);t=putint(a15);
      t=putint(a16);t=putint(a17);t=putint(a18);t=putint(a19);
      t=putint(a20);t=putint(a21);t=putint(a22);t=putint(a23);
      t=putint(a24);t=putint(a25);
      int newline;
      newline = 10;
      t=putchar(newline);
      t=putint(b);
      t=putchar(newline);
      return a25;
   }


int main(){
	return 0;
}


int a;
int main(){
	a=10;
	return 0;
}


int a;
int b;
int main(){
	a=10;
	int c;
	c=10;
	return 0;
}


int a[10];
int main(){
	return 0;
}


int a;
int func(int p){
	p = p - 1;
	return p;
}
int main(){
	int b;
	a = 10;
	b = func(a);
	return b;
}


int a;
int b;

int main(){
	a=10;
	b=20;
	int c;
	c = a + b;
	return c;
}


int a;
int b;
int main(){
	a = 10;
	b = 3;
	int c;
	c = a % b;
	return c;
}


int a;

int main(){
	a=10;
	return a;
}


int a[10];
int main(){
	a[0]=1;
	return 0;
}


int a;

int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	return 0;
}


int a;
int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int main(){
	b=0;
	a=3;
	while(a>0){	
		b = b+a;
		a = a-1;
	}
	return b;
}	


int getint();
int main(){
	int a;
	a = getint();
	return a;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a && b ) {
		return 1;
	}
	else {
		return 0;
	}
}


int a;
int b;
int getint();
int main() {
	a = getint();
	b = getint();
	if ( a || b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a == b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a != b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a < b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int c;
int getint();
int main(){
	a = getint();
	b = getint();
	c = getint();
	int d;
	d = a+b*c;
	return d;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	int c;
	c = -(a + b);
	return c;
}


int getint();
int a[5];
int main(){
	a[0] = getint();
	a[1] = getint();
	a[2] = getint();
	a[3] = getint();
	a[4] = getint();
	int cnt;
	cnt = 4;
	int sum;
	sum = 0;
	while( cnt > 1 ){
		sum = sum + a[cnt];
		cnt = cnt - 1;
	}
	return sum;
}


int putint(int i);
int getint();
int n;
int fib(int p){
	int a;
	int b;
	int c;
	a = 0;
	b = 1;
	if ( p == 0 ){
		return 0;
	}
	if ( p == 1 ){
		return 1;
	}
	while ( p > 1 ){
		c = a + b;
		a = b;
		b = c;
		p = p - 1;
	}
	return c;
}
int main(){
	n = getint();
	int res;
	res = fib( n );
	return res;
}


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


//sample:input n number, sort them and print them;
   int n;
   int getint();
   int putint(int i);
   int putchar(int c);
   int main()
   {
      int a0;
      int a1;
      int a2;
      int a3;
      int a4;
      int a5;
      int a6;
      int a7;
      int a8;
      int a9;
      int a10;
      int a11;
      int a12;
      int a13;
      int a14;
      int a15;
      int a16;
      int a17;
      int a18;
      int a19;
      int a20;
      int a21;
      int a22;
      int a23;
      int a24;
      int a25;
      int b;
      b = getint();
      while(b == 5){
          b = b + 1;
      }
      a0=0;
      a1=a0+1;
      a2=a1+1;
      a3=a2+1;
      a4=a3+1;
      a5=a4+1;
      a6=a5+1;
      a7=a6+1;
      a8=a7+1;
      a9=a8+1;
      a10=a9+1;
      a11=a10+1;
      a12=a11+1;
      a13=a12+1;
      a14=a13+1;
      a15=a14+1;
      a16=a15+1;
      a17=a16+1;
      a18=a17+1;
      a19=a18+1;
      a20=a19+1;
      a21=a20+1;
      a22=a21+1;
      a23=a22+1;
      a24=a23+1;
      a25=a24+1;
      int t;
      t=putint(a0);t=putint(a1);t=putint(a2);t=putint(a3);
      t=putint(a4);t=putint(a5);t=putint(a6);t=putint(a7);
      t=putint(a8);t=putint(a9);t=putint(a10);t=putint(a11);
      t=putint(a12);t=putint(a13);t=putint(a14);t=putint(a15);
      t=putint(a16);t=putint(a17);t=putint(a18);t=putint(a19);
      t=putint(a20);t=putint(a21);t=putint(a22);t=putint(a23);
      t=putint(a24);t=putint(a25);
      int newline;
      newline = 10;
      t=putchar(newline);
      t=putint(b);
      t=putchar(newline);
      return a25;
   }


int main(){
	return 0;
}


int a;
int main(){
	a=10;
	return 0;
}


int a;
int b;
int main(){
	a=10;
	int c;
	c=10;
	return 0;
}


int a[10];
int main(){
	return 0;
}


int a;
int func(int p){
	p = p - 1;
	return p;
}
int main(){
	int b;
	a = 10;
	b = func(a);
	return b;
}


int a;
int b;

int main(){
	a=10;
	b=20;
	int c;
	c = a + b;
	return c;
}


int a;
int b;
int main(){
	a = 10;
	b = 3;
	int c;
	c = a % b;
	return c;
}


int a;

int main(){
	a=10;
	return a;
}


int a[10];
int main(){
	a[0]=1;
	return 0;
}


int a;

int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	return 0;
}


int a;
int main(){
	a = 10;
	if( a>0 ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int main(){
	b=0;
	a=3;
	while(a>0){	
		b = b+a;
		a = a-1;
	}
	return b;
}	


int getint();
int main(){
	int a;
	a = getint();
	return a;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a && b ) {
		return 1;
	}
	else {
		return 0;
	}
}


int a;
int b;
int getint();
int main() {
	a = getint();
	b = getint();
	if ( a || b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a == b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a != b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	if ( a < b ){
		return 1;
	}
	else{
		return 0;
	}
}


int a;
int b;
int c;
int getint();
int main(){
	a = getint();
	b = getint();
	c = getint();
	int d;
	d = a+b*c;
	return d;
}


int a;
int b;
int getint();
int main(){
	a = getint();
	b = getint();
	int c;
	c = -(a + b);
	return c;
}


int getint();
int a[5];
int main(){
	a[0] = getint();
	a[1] = getint();
	a[2] = getint();
	a[3] = getint();
	a[4] = getint();
	int cnt;
	cnt = 4;
	int sum;
	sum = 0;
	while( cnt > 1 ){
		sum = sum + a[cnt];
		cnt = cnt - 1;
	}
	return sum;
}


int putint(int i);
int getint();
int n;
int fib(int p){
	int a;
	int b;
	int c;
	a = 0;
	b = 1;
	if ( p == 0 ){
		return 0;
	}
	if ( p == 1 ){
		return 1;
	}
	while ( p > 1 ){
		c = a + b;
		a = b;
		b = c;
		p = p - 1;
	}
	return c;
}
int main(){
	n = getint();
	int res;
	res = fib( n );
	return res;
}


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


//sample:input n number, sort them and print them;
   int n;
   int getint();
   int putint(int i);
   int putchar(int c);
   int main()
   {
      int a0;
      int a1;
      int a2;
      int a3;
      int a4;
      int a5;
      int a6;
      int a7;
      int a8;
      int a9;
      int a10;
      int a11;
      int a12;
      int a13;
      int a14;
      int a15;
      int a16;
      int a17;
      int a18;
      int a19;
      int a20;
      int a21;
      int a22;
      int a23;
      int a24;
      int a25;
      int b;
      b = getint();
      while(b == 5){
          b = b + 1;
      }
      a0=0;
      a1=a0+1;
      a2=a1+1;
      a3=a2+1;
      a4=a3+1;
      a5=a4+1;
      a6=a5+1;
      a7=a6+1;
      a8=a7+1;
      a9=a8+1;
      a10=a9+1;
      a11=a10+1;
      a12=a11+1;
      a13=a12+1;
      a14=a13+1;
      a15=a14+1;
      a16=a15+1;
      a17=a16+1;
      a18=a17+1;
      a19=a18+1;
      a20=a19+1;
      a21=a20+1;
      a22=a21+1;
      a23=a22+1;
      a24=a23+1;
      a25=a24+1;
      int t;
      t=putint(a0);t=putint(a1);t=putint(a2);t=putint(a3);
      t=putint(a4);t=putint(a5);t=putint(a6);t=putint(a7);
      t=putint(a8);t=putint(a9);t=putint(a10);t=putint(a11);
      t=putint(a12);t=putint(a13);t=putint(a14);t=putint(a15);
      t=putint(a16);t=putint(a17);t=putint(a18);t=putint(a19);
      t=putint(a20);t=putint(a21);t=putint(a22);t=putint(a23);
      t=putint(a24);t=putint(a25);
      int newline;
      newline = 10;
      t=putchar(newline);
      t=putint(b);
      t=putchar(newline);
      return a25;
   }


