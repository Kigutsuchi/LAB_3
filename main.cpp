#include <iostream>
#include <stdlib.h>

using namespace std;

int cmp(const void* a, const void* b)
{
	const double* ad, * bd;

	ad = (const double*)a;
	bd = (const double*)b;

	if (*ad < *bd)
	{
		return -1;
	}
	else if (*ad > * bd)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

class Array
{
private:

public:
	double* arr;
	int size;
	Array()
	{
		this->arr = NULL;
		this->size = 0;
	}
	Array(int t_size)
	{
		this->size = t_size;
		this->arr = new double[this->size];
		for(int i = 0; i < this->size; i++)
			cin >> this->arr[i];
	}
	Array(const Array& cpy)
	{
		this->size = cpy.size;
		this->arr = new double[cpy.size];
		for (int i = 0; i < this->size; i++)
			this->arr[i] = cpy.arr[i];
	}
	~Array()
	{
		delete[] arr;
	}

	void showObject(Array& temp)
	{
		cout << "Size of array: " << temp.size << ". Select array element number: ";
		int index;
		do {
			cin >> index;
		} while (index < 1 && index > temp.size);
		cout << "Searched element:" << temp.arr[index - 1];
	}
	void recordObject(Array& temp)
	{
		cout << "Size of array: " << temp.size << ". Select array element number: ";
		int index;
		do {
			cin >> index;
		} while (index < 1 && index > temp.size);
		int data;
		cin >> data;
		temp.arr[index - 1] = data;
	}
	void showArr(Array& temp)
	{
		for (int i = 0; i < temp.size; i++)
		{
			cout << temp.arr[i] << " ";
		}
	}
	void sortArr(Array& temp)
	{
		qsort(temp.arr, temp.size, sizeof(double), cmp);
	}
	void re_allocation(Array& res, double data)
	{
		double* temp = new double[res.size];
		if (res.arr == NULL)
		{
			temp[0] = data;
			res.arr = temp;
			return;
		}
		for (int i = 0; i < res.size - 1; i++)
			temp[i] = res.arr[i];
		temp[res.size - 1] = data;
		res.arr = temp;
	}
	bool crossing(Array& crs, double tmp)
	{
		if (crs.arr == NULL)
			return false;
		for (int i = 0; i < crs.size; i++)
			if (crs.arr[i] == tmp)
				return true;
		return false;
	}

	void menu(Array& temp)
	{
		cout << "Choose an option:" << endl;
		cout << "1.Reading an object" << endl;
		cout << "2.Object recording" << endl;
		cout << "3.Show entire array" << endl;
		cout << "4.Sorting an array" << endl;
		int choise;
		do {
			cin >> choise;
		} while (choise < 1 && choise > 4);
		switch (choise)
		{
		case 1:
			showObject(temp);
			break;
		case 2:
			recordObject(temp);
			break;
		case 3:
			showArr(temp);
			break;
		case 4:
			sortArr(temp);
			break;
		}
	}

	Array operator& (Array temp)
	{
		Array res;
		for (int i = 0; i < this->size; i++)
		{
			if (crossing(res, this->arr[i]))
				continue;
			
			for (int j = 0; j < temp.size; j++)
			{
				if (this->arr[i] == temp.arr[j])
				{
					res.size++;
					re_allocation(res, this->arr[i]);
					break;
				}
			}
		}
		return res;
	}
	Array& operator= (Array temp)
	{
		this->size = temp.size;
		this->arr = new double[this->size];
		for (int i = 0; i < this->size; i++)
			this->arr[i] = temp.arr[i];
		return *this;
	}
	Array& operator++ ()
	{
		for (int i = 0; i < this->size; i++)
			this->arr[i]++;
		return *this;
	}

	friend Array operator+(const Array& temp_1, const Array& temp_2);
	friend Array operator+(const Array& temp_1, double data);
	friend Array operator-(const Array& temp_1, const Array& temp_2);
	friend Array operator-(const Array& temp_1, double data);
};

Array operator+(const Array& temp_1, const Array& temp_2)
{
	if (temp_1.size <= temp_2.size)
	{
		Array res;
		res.size = temp_1.size;
		res.arr = new double[temp_1.size];
		for (int i = 0; i < res.size; i++)
			res.arr[i] = temp_1.arr[i] + temp_2.arr[i];
		return res;
	}
	else
	{
		Array res;
		res.size = temp_2.size;
		res.arr = new double[temp_2.size];
		for (int i = 0; i < res.size; i++)
			res.arr[i] = temp_1.arr[i] + temp_2.arr[i];
		return res;
	}
}
Array operator+(const Array& temp_1, double data)
{
	Array res;
	res.size = temp_1.size;
	res.arr = new double[temp_1.size];
	for (int i = 0; i < res.size; i++)
		res.arr[i] = temp_1.arr[i] + data;
	return res;
}
Array operator-(const Array& temp_1, const Array& temp_2)
{
	if (temp_1.size <= temp_2.size)
	{
		Array res;
		res.size = temp_1.size;
		res.arr = new double[temp_1.size];
		for (int i = 0; i < res.size; i++)
			res.arr[i] = temp_1.arr[i] - temp_2.arr[i];
		return res;
	}
	else
	{
		Array res;
		res.size = temp_2.size;
		res.arr = new double[temp_2.size];
		for (int i = 0; i < res.size; i++)
			res.arr[i] = temp_1.arr[i] - temp_2.arr[i];
		return res;
	}
}
Array operator-(const Array& temp_1, double data)
{
	Array res;
	res.size = temp_1.size;
	res.arr = new double[temp_1.size];
	for (int i = 0; i < res.size; i++)
		res.arr[i] = temp_1.arr[i] - data;
	return res;
}


int main()
{
	Array first = Array(5);
	Array second = Array(3);
	Array third = Array();
	third = first - 5.45;
	first.menu(first);
	first.menu(first);
	third.menu(third);
	return 0;
}