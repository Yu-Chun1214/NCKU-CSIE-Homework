#include <iostream>
#include <string>

using namespace std;

int main(){
	int a[5] = {1 , 2, 3, 4, 5};
	int (*p)[5][5];
	int aa[5][5];
	p = &aa;
	printf("%p\n",aa);
	printf("%p\n",*p);
	cout<<p[0][1]<<endl;
}

/*
int (*p)[10];
p 的型態是 int (*)[10]
p 的型態叫做array pointer，指的是p可以(只能)指向 int a[10] 大小為10的陣列
意思就是 p = &a是合法的。
當developer需透過p使用a裡的element時，
需要寫(*p)[i]來取得a[i]的值，這是因為*的precedence 比[]低(雖然兩個運算子的意義都是取值XD)所以需要使用()

int (*p)[10][10]，p只能指向int aa[5][5]; 意思就是 p = &aa;

如果是宣告
int *p[10]
代表p裡的每個element都是 int * 型態的變數
因此可以寫 int a[10]; p[0] = a;
*/