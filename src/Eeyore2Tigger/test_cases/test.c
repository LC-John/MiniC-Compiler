int a;
int b;
int c;
int getint();

int main(){
	a = getint();
	b = getint();
	if (a > b)
		c = a;
	else
		c = b;
	return c;
}
