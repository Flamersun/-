
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;
int sundaram(int n)
{
	int* a = new int[n], i, j, k;
	memset(a, 0, sizeof(int) * n);
	for (i = 1; 3 * i + 1 < n; i++)
	{
		for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++)
			a[k] = 1;
	}
	for (i = n - 1; i >= 1; i--)
		if (a[i] == 0)
		{
			return (2 * i + 1);
			break;
		}
	delete[] a;
}

int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}

int main()
{
	setlocale(LC_ALL, "");
	cout << "�������������� �����:" << endl << endl;
	srand((unsigned)time(NULL));
	int p = rand() % 100;
	int q = rand() % 100;
	int p_simple = sundaram(p);
	int q_simple = sundaram(q);
	unsigned int n = p_simple * q_simple;
	int d, d_simple = 0;
	while (d_simple != 1)
	{
		d = rand() % 100;
		d_simple = gcd(d, ((p_simple - 1) * (q_simple - 1)));
	}
	unsigned int e = 0, e_simple = 0;
	while (e_simple != 1)
	{
		e += 1;
		e_simple = (e * d) % ((p_simple - 1) * (q_simple - 1));
	}
	cout << '(' << setw(5) << e << ',' << setw(5) << n << ')' << " - �������� ����" << endl;
	cout << '(' << setw(5) << d << ',' << setw(5) << n << ')' << " - ��������� ����" << endl << endl;
	const int MAX = 30;
	char* Text = new char[MAX];
	cout << "������� ����� ��� �������� � ������� Enter" << endl;
	cin.get(Text, MAX);
	unsigned int* CryptoText = new unsigned int[MAX];
	unsigned int* Tdecrypt = new unsigned int[MAX];
	int b = 301;
	int c;
	cout << endl << setw(5) << "�����" << setw(6) << "ASCII"
		<< setw(20) << "�����������" << setw(14)
		<< "ASCII �����������" << setw(14) << "����������� ������" << endl
		<< "------------------------------------------------------------" << endl;
	for (int j = 0; j < MAX; j++)
	{
		c = 1;
		unsigned int i = 0;
		int ASCIIcode = (static_cast<int>(Text[j])) + b;
		while (i < e)
		{
			c = c * ASCIIcode;
			c = c % n;
			i++;
		}
		CryptoText[j] = c;
		b += 1;
	}
	b = 301;
	int m;
	for (int j = 0; j < MAX; j++)
	{
		m = 1;
		unsigned int i = 0;
		while (i < d)
		{
			m = m * CryptoText[j];
			m = m % n;
			i++;
		}
		m = m - b;
		Tdecrypt[j] = m;
		b += 1;
	}
	for (int j = 0; j < MAX; j++)
	{
		cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) << setw(20)
			<< CryptoText[j] << setw(14) << Tdecrypt[j] << setw(14) << static_cast<char>(Tdecrypt[j]) << endl;
	}
	delete[] Text;
	delete[] CryptoText;
	delete[] Tdecrypt;
	return 0;
}

int _tmain(int argc, char argv[])
{

	return 0;
}