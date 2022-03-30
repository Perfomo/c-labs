#include <iostream>
#include <stdio.h>
// #include <conio.h>
#include <locale.h>
#include <string>
#include <ctime>
//#include <sstream>
using namespace std;
#include "Source1.h"


bool odouble(string x)
{
	int num = 0, k, z, num1 = 0, s = x.length();

	const string u = "1234567890-.,";
	if ((s == 1) and (x[0] == '-'))
	{
		return false;
	}
	if (x[1] == '-' or (s == 1 and (x[0] == ',' or x[0] == '.')) or (s == 2 and (x[1] == ',' or x[1] == '.')))
	{
		return false;
	}

	for (k = 1; k <= (s - 1); k += 1)
	{
		if (x[k] == '-')
		{
			return false;
		}
	}


	for (k = 0; k <= (s - 1); k += 1)
	{
		if ((x[k] == '.') or (x[k] == ','))
		{
			x[k] = ',';
			num1 += 1;
			num += 1;
		}


		if ((num1 == 2) or (x[k] == ' '))
		{

			return false;
		}

		for (z = 0; z <= 10; z += 1)
		{
			if (x[k] == u[z])
			{
				num += 1;
			}
			else
			{
				continue;
			}
		}

	}

	if (num == s)
	{

		return true;
	}
	else
	{

		return false;
	}
}



double InputDouble(string rool)
{
	bool accept;
	int num1 = 0, ks;
	string x;
	double res;
	while (num1 == 0)
	{
		cin >> x;
		accept = odouble(x);

		if (accept)
		{
			for (ks = 0; ks <= (x.length() - 1); ks += 1)
			{
				if (x[ks] == ',')
				{
					x[ks] = '.';
				}
			}
			if (x[0] == '.')
			{
				x = "0" + x;
			}
			if (rool == ">0" and stod(x) <= 0)
			{
				cout << "Bad input..." << endl;
			}
			else {
				return stof(x);
			}
		}
		else
		{
			cout << "Bad input..." << endl;
		}
	}
}


bool oint(string x, string rool_1)
{
	int num = 0, k, z, num1 = 0, s = x.length();

	const string plus = "1234567890";
	const string all = "1234567890-";

	if (rool_1 == ">=0")
	{
		for (k = 0; k <= (s - 1); k += 1)
		{
			for (z = 0; z <= 9; z += 1)
			{
				if (x[k] == plus[z])
				{
					num += 1;
				}
				else
				{
					continue;
				}
			}
		}
	}
	if (rool_1 == ">1")
	{
		if (x[0] == '0' || (x[0] == '1' && x.length() == 1))
		{
			return false;
		}
		for (k = 0; k <= (s - 1); k += 1)
		{
			for (z = 0; z <= 9; z += 1)
			{
				if (x[k] == plus[z])
				{
					num += 1;
				}
				else
				{
					continue;
				}
			}
		}
	}
	if (rool_1 == ">0")
	{
		if (x[0] == '0')
		{
			return false;
		}
		for (k = 0; k <= (s - 1); k += 1)
		{
			for (z = 0; z <= 9; z += 1)
			{
				if (x[k] == plus[z])
				{
					num += 1;
				}
				else
				{
					continue;
				}
			}
		}
	}
	if (rool_1 == "all")
	{
		for (k = 0; k <= (s - 1); k += 1)
		{
			for (z = 0; z <= 10; z += 1)
			{
				if (x[k] == all[z])
				{
					num += 1;
				}
				else
				{
					continue;
				}
			}
			if (k != 0 and x[k] == '-')
			{
				return false;
			}
		}
		if ((s == 1) and (x[0] == '-'))
		{
			return false;
		}
	}
	if (rool_1 == "0-10")
	{
		for (k = 0; k <= (s - 1); k += 1)
		{
			for (z = 0; z <= 9; z += 1)
			{
				if (x[k] == plus[z])
				{
					num += 1;
				}
				else
				{
					continue;
				}
			}
		}
		if (x.length() >= 2 and x != "10")
		{
			return false;
		}
	}
	if (rool_1 == "1964-2004")
	{
		for (k = 0; k <= (s - 1); k += 1)
		{
			for (z = 0; z <= 9; z += 1)
			{
				if (x[k] == plus[z])
				{
					num += 1;
				}
				else
				{
					continue;
				}
			}
		}
		if (num == s)
		{
			int np = stoi(x);
			if (x.length() != 4 or np > 2004 or np < 1964)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}

	}
	if (num == s)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int InputInt(string rool_1)
{
	string x;
	while (true)
	{
		cin >> x;
		if (oint(x, rool_1))
		{
			return stoi(x);
		}
		else
		{
			cout << "Bad input..." << endl;
		}
	}
}


#include <termios.h>
#include <unistd.h>
int _getch(void)
{
struct termios oldattr, newattr;
int ch;

tcgetattr(STDIN_FILENO, &oldattr);
newattr = oldattr;
newattr.c_lflag &= ~(ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
ch = getchar();
tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
return ch;
}