/* При переопределении операторов ввода-вывода нужно в качестве возвращаемого
 * значения указывать ссылки на эти же потоки, это нужно, чтобы иметь 
 * возможность считывать или выводить в поток данных несколько лексем подряд.
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Date {
	string day;
	string hour;

	Date(int d = 0, int h = 0) {
		day = d;
		h = 0;
	}
};

istream& operator>>(istream& stream, Date& date)
{
	stream >> date.day;
	stream.ignore(1);
	stream >> date.hour;
	return stream;
}

ostream& operator<<(ostream& stream, Date& date)
{
	stream << date.day << ' ' << date.hour;
	return stream;
}

int main()
{
	stringstream my_str("19.01.2001 19:00");
	Date d;
	my_str >> d;
	cout << d << endl;
}
