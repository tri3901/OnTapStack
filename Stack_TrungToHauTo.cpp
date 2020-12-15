#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char sTemp[100];

struct Node
{
	char info;
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

Node *taoNode(char c)
{
	Node *p = new Node;
	if (p != NULL)
	{
		p->info = c;
		p->next = NULL;
	}
	return p;
}

void push(Stack &stack, char c)
{
	Node *p = taoNode(c);
	if (p == NULL) return;
	if (kiemTraRong(stack))
		stack.top = p;
	else
	{
		p->next = stack.top;
		stack.top = p;
	}
}

char pop(Stack &stack, char &c)
{
	if (kiemTraRong(stack)) return '\0';
	else
	{
		Node *p = stack.top;
		stack.top = p->next;
		c = p->info;
		return c;
		delete p;
	}
}

int doUuTien(char c)
{
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	if (c == '^')
		return 3;
	return 0;
}

void chuyenDoiBieuThuc(Stack &stack, char s[], int n)
{
	khoiTaoStack(stack);
	int j = 0;
	char c;
	for (int i = 0; i < n; i++)
	{
		if (s[i] >= '0' && s[i] <= '9' || s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z')
		{
			sTemp[j] = s[i];
			j++;
		}
		else if (s[i] == '(')
			push(stack, s[i]);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '^' || s[i] == '*')
		{
			if (kiemTraRong(stack))
				push(stack, s[i]);
			else if (doUuTien(stack.top->info) >= doUuTien(s[i]))
			{
				c = pop(stack, c);
				sTemp[j] = c;
				j++;
				push(stack, s[i]);
			}
			else
				push(stack, s[i]);
		}
		else if (s[i] == ')')
		{
			while (!kiemTraRong(stack) && stack.top->info != '(')
			{
				c = pop(stack, c);
				sTemp[j] = c;
				j++;
			}
		}
	}
	while (!kiemTraRong(stack))
	{
		c = pop(stack, c);
		if (c == '(' || c == ')')
			continue;
		else
		{
			sTemp[j] = c;
			j++;
		}
	}
}

bool kiemTraXauNgoac(Stack &stack, char s[], int n)
{
	khoiTaoStack(stack);
	char c;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			push(stack, s[i]);
		else
		{
			if (!kiemTraRong(stack))
			{
				if (s[i] == ')')
				{
					if (stack.top->info != '(')
						return false;
				}
				if (s[i] == ']')
				{
					if (stack.top->info != '[')
						return false;
				}
				if (s[i] == '}')
				{
					if (stack.top->info != '{')
						return false;
				}
				pop(stack, c);
			}
			else return false;
		}
	}
	return true;
}

int tinhBieuThucHauTo(Stack &stack, char s[], int n) //error
{
	khoiTaoStack(stack);
	char c;
	int a, b, final;
	for (int i = 0; i < n; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
			push(stack, s[i]);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '^' || s[i] == '*')
		{
			a = (int)stack.top->info;
			pop(stack, c);
			b = (int)stack.top->info;
			pop(stack, c);
			switch (s[i])
			{
			case '+':
			{
						final = a + b;
						break;
			}
			case '-':
			{
						final = a - b;
						break;
			}
			case '*':
			{
						final = a * b;
						break;
			}
			case '/':
			{
						final = a / b;
						break;
			}
			case '^':
			{
						final = b;
						for (int i = 0; i < a - 1; i++)
						{
							final *= b;
						}
						break;
			}
			default:
				break;
			}
			push(stack, (char)final);
		}
	}
	final = (int)pop(stack, c);
	return final;
}

void main()
{
	Stack stack;
	char s[100];
	printf("Nhap bieu thuc trung to/xau ngoac: ");
	scanf("%s", s);
	int n = strlen(s);

	printf("Tong ket qua: %d", tinhBieuThucHauTo(stack, s, n));

	/*if (kiemTraXauNgoac(stack, s, n))
		printf("Xau ngoac hop le");
	else
		printf("Xau ngoac khong hop le");*/

	/*chuyenDoiBieuThuc(stack, s, n);
	for (int i = 0; i < strlen(sTemp); i++)
	{
		printf("%c", sTemp[i]);
	}*/

	printf("\n");
	system("pause");
}