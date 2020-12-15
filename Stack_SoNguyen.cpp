#include <stdio.h>
#include <stdlib.h>

struct Node
{	
	int info;
	Node *next;
};

struct Stack
{
	Node *top;
};

void khoiTaoStack(Stack &stack)
{
	stack.top = NULL;
}

bool kiemTraRong(Stack stack)
{
	return stack.top == NULL;
}

Node *taoNode(int x)
{
	Node *p = new Node;
	if (p != NULL)
	{
		p->info = x;
		p->next = NULL;
	}
	return p;
}

void push(Stack &stack, int x)
{
	Node *p = taoNode(x);
	if (p == NULL) return;
	if (kiemTraRong(stack))
		stack.top = p;
	else
	{
		p->next = stack.top;
		stack.top = p;
	}
}

void pop(Stack &stack, int &x)
{
	if (kiemTraRong(stack)) return;
	else
	{
		Node *p = stack.top;
		stack.top = p->next;
		x = p->info;
		delete p;
	}
}

int tinhGiaiThua(int n)
{
	Stack s;
	khoiTaoStack(s);
	int ketQua = 1;
	while (n > 0)
	{
		push(s, n);
		n--;
	}
	while (!kiemTraRong(s))
	{
		int x;
		pop(s, x);
		ketQua *= x;
	}
	return ketQua;
}

void chuyenDoiHeCoSo(int n, int heSo)
{
	Stack s;
	khoiTaoStack(s);
	while (n > 0)
	{
		int temp = n % heSo;
		n /= heSo;
		push(s, temp);
	}
	while (!kiemTraRong(s))
	{
		int x;
		pop(s, x);
		if (x > 10)
			printf("%d", x);
		else
			printf("%X", x);
	}
}

void main()
{
	int x, heSo;
	printf("Nhap x: ");
	scanf("%d", &x);
	printf("Nhap he co so: ");
	scanf("%d", &heSo);
	chuyenDoiHeCoSo(x, heSo);
	//printf("Ket qua: %d", tinhGiaiThua(x));
	printf("\n");
	system("pause");
}