int a;
int b;
int c;
int getint();

int func(int a, int res)
{
	if (a < 0 || a == 0)
		return res;
	res = res + a;
	a = a - 1;
	int ret;
	ret = func(a, res);
	return ret;
}

int main(){
	a = getint();
	b = 0;
	c = func(a, b);
	return c;
}
