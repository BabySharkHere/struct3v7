/*Вариант 7 
Порядок: по возрастанию элементов. Методы: простых вставок, бинарных вставок, 
Шелла (шаг сортировки hk-1=3hk+1, ht=1, t=log3n-1 и hk-1=2hk+1, ht=1, t=log2n-1). N1=10000, 
N2=30000, N3=70000, N4=100000. Критерий – количество сравнений.*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

struct sortAlgorithms {
	
	int n; //количество чисел, которые нам необходимо загрузить из файла
	int* mass; //массив, в которй считываем числа из файла
	int* massOrder; //массив, упорядоченный по убыванию
	int* z; //массив, с которым работаем
	unsigned long long int other; //счётчик вспомогательных сравнений
	float startTime = 0; //переменная, для того, чтобы узнать время начала работы алгоритма
	float endTime = 0; //переменная, для того, чтобы узнать время окончания работы алгорима
	
	void upToDown() { //функция, которая переприсваивает массиву z массив, упорядоченный по убыванию
			for (int i = 0; i < n; i++)
				z[i] = massOrder[i];
	}
	
	void differentToUp() { //функиця, которая переприсваивает массиву z массив, считанный из файла
			for (int i = 0; i < n; i++)
				z[i] = mass[i];
	}
	
	void loadFile() { //функция, которая считывает числа из файла
		ifstream file("test_numbers.txt");
		if (!file) {
			cout << "Ошибка открытия файла!" << endl;
			exit(0);
		}
		for (int i = 0; i < n; i++) {
			file >> mass[i];
		}
	}
	
	void choice() { //функция, в которой мы выбираем N1-N4(количество чисел, которые нужно отсортировать)
		int choice;
		cout << "Выберите количество чисел для обработки:" << endl;
		cout << "1. 10.000" << endl;
		cout << "2. 30.000" << endl;
		cout << "3. 70.000" << endl;
		cout << "4. 100.000" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			n = 10000;
			mass = new int[n];
			z = new int[n];
			loadFile();
			break;
		}
		case 2: {
			n = 30000;
			mass = new int[n];
			z = new int[n];
			loadFile();
			break;
		}
		case 3: {
			n = 70000;
			mass = new int[n];
			z = new int[n];
			loadFile();
			break;
		}
		case 4: {
			n = 100000;
			mass = new int[n];
			z = new int[n];
			loadFile();
			break;
		}
		}
	}
	void sortToDown() //функция, сортирующая массив по убыванию
	{
		massOrder = new int[n];
		for (int i = 0; i < n; i++)
			massOrder[i] = mass[i];
		int max = INT_MIN;
		int min = INT_MAX;
		int L;
		int k;
		for (int i = 0; i < n; i++)
		{
			if (massOrder[i] > max) {
				max = massOrder[i];
			}
			if (massOrder[i] < min) {
				min = massOrder[i];
			}
		}
		L = max - min + 1;
		int* B = new int[L];
		for (int i = 0; i < L; i++)
		{
			B[i] = 0;
		}
		for (int i = 0; i < n; i++)
		{
			B[massOrder[i] - min]++;
		}
		k = 0;
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < B[i]; j++)
			{
				massOrder[k++] = (i - max) * -1;
			}
		}
		delete[] B;
	}
	void insertionSort() // сортировка вставками
	{
		unsigned long long int flagInsertion = 0;
		other = 0;
		startTime = clock();
		int temp, // временная переменная для хранения значения элемента сортируемого массива
			item; // индекс предыдущего элемента
		for (int counter = 1; counter < n; counter++)
		{
			temp = z[counter]; // инициализируем временную переменную текущим значением элемента массива
				item = counter - 1; // запоминаем индекс предыдущего элемента массива
				//flagInsertion++;
				//other++;
			while (item >= 0 && z[item] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
			{
			z[item + 1] = z[item]; // перестановка элементов массива
			z[item] = temp;
			item--;
			flagInsertion++;
			other++;
			}
			other++;
		}
		endTime = clock();
		float timeInsertion = (endTime - startTime) / CLOCKS_PER_SEC;
		int size = sizeof(temp) + sizeof(item);
		for (int i = 0; i < 5; i++)
			cout << "[" << i << "] " << z[i] << endl;
		cout << "Количество времени, которое потребовалось для обработки массива методом вставки : " << timeInsertion << " секунд" << endl;
			cout << "Количество сравнений в методе сортировки вставками: " <<
			flagInsertion << endl;
		cout << "Количество вспомогательных сравнений: " << other << endl;
		cout << "Количество дополнительно требуемой памяти: " << size << " байта"
			<< endl;
	}
	void sortArrayBinary() { //метод бинарных
		unsigned long long int flagBinary = 0;
		other = 0;
		int x;
		int left;
		int right;
		int sred;
		startTime = clock();
		for (int i = 1; i < n; i++)
			if (z[i - 1] > z[i]) {
				x = z[i];
				flagBinary++;
				left = 0;
				right = i - 1;
				other += 2;
				do {
					sred = (left + right) / 2;
					if (z[sred] < x) {
						left = sred + 1;
						other++;
					}
					else {
						right = sred - 1;
						other++;
					}
					other++;
				} while (left <= right);
				for (int j = i - 1; j >= left; j--) {
					z[j + 1] = z[j];
					flagBinary++;
				}
				z[left] = x;
				other++;
			}
		endTime = clock();
		float timeBinary = (endTime - startTime) / CLOCKS_PER_SEC;
		int size = sizeof(x) + sizeof(left) + sizeof(right) + sizeof(sred);
		for (int i = 0; i < 5; i++)
			cout << "Binary[" << i << "] " << z[i] << endl;
		cout << "Количество времени, которое потребовалось для обработки массива методом бинарных вставок : " << timeBinary << " секунд" << endl;
			cout << "Количество сравнений в методе сортировки бинарными вставками: " <<
			flagBinary << endl;
		cout << "Количество вспомогательных сравнений: " << other << endl;
		cout << "Количество дополнительно требуемой памяти: " << size << " байта"
			<< endl;
	}
	void Shell() { //сортировка методом Шелла
		unsigned long long int flagShell = 0;
		other = 0;
		int m, x, j, i, k;
		const int t = log(n - 1) / log(3);
		int* h = new int[t];
		h[t - 1] = 1;
		other++;
		startTime = clock();
		for (m = t - 2; m >= 0; m--) {
			h[m] = h[m + 1] * 3 + 2;
			other++;
		}
		for (m = 0; m < t; m++) {
			k = h[m];
			for (i = k; i < n; i++) {
				x = z[i];
				j = i - k;
				while (j >= 0 && x < z[j]) {
						z[j + k] = z[j];
					j -= k;
					flagShell++;
					other++;
				}
				z[j + k] = x;
				//flagShell += 2;
				other++;
			}
			other++;
		}
		endTime = clock();
		float timeShell = (endTime - startTime) / CLOCKS_PER_SEC;
		int size = sizeof(m) + sizeof(x) + sizeof(j) + sizeof(i) + sizeof(k) +
			sizeof(h) + sizeof(t);
		for (int i = 0; i < 5; i++)
			cout << "Shell[" << i << "] " << z[i] << endl;
		cout << "Количество времени, которое потребовалось для обработки массива методом Шелла : " << timeShell << " секунд" << endl;
			cout << "Количество присваиваний в методе соритровке Шелла " << flagShell
			<< endl;
		cout << "Количество вспомогательных сравнений: " << other << endl;
		cout << "Количество дополнительно требуемой памяти: " << size << " байта"
			<< endl;
		delete[] h;
	}

	void ShellSecond() {
		unsigned long long int flagShell = 0;
		other = 0;
		int m, x, j, i, k;
		const int t = log(n - 1) / log(2);
		int* h = new int[t];
		h[t - 1] = 1;
		other++;
		startTime = clock();

		for (m = t - 2; m >= 0; m--) {
			h[m] = h[m + 1] * 2 + 2;
			other++;
		}

		for (m = 0; m < t; m++) {
			k = h[m];
			for (i = k; i < n; i++) {
				x = z[i];
				j = i - k;
				while (j >= 0 && x < z[j]) {
					z[j + k] = z[j];
					j -= k;
					flagShell++;
					other++;
				}
				z[j + k] = x;
				//flagShell += 2;
				other++;
			}
			other++;
		}
		endTime = clock();
		float timeShell = (endTime - startTime) / CLOCKS_PER_SEC;
		int size = sizeof(m) + sizeof(x) + sizeof(j) + sizeof(i) + sizeof(k) +
			sizeof(h) + sizeof(t);
		for (int i = 0; i < 5; i++)
			cout << "Shell[" << i << "] " << z[i] << endl;
		cout << "Количество времени, которое потребовалось для обработки массива методом Шелла : " << timeShell << " секунд" << endl;
		cout << "Количество присваиваний в методе соритровке Шелла " << flagShell
			<< endl;
		cout << "Количество вспомогательных сравнений: " << other << endl;
		cout << "Количество дополнительно требуемой памяти: " << size << " байта"
			<< endl;
		delete[] h;
	}
	~sortAlgorithms() { //деструктор
		delete[] mass;
		delete[] z;
		delete[] massOrder;
		cout << "Деструктор активирован!" << endl;
	}
};
int main() {
	setlocale(LC_ALL, "ru");
	sortAlgorithms a;
	a.choice();
	a.sortToDown();
	int change;
	do {
		cout << "Выберите алгоритм сортировки:" << endl;
		cout << "1. Методом простых вставок" << endl;
		cout << "2. Методом бинарных вставок" << endl;
		cout << "3. Методом Шелла" << endl;
		cout << "4. Методом Шелла со вторым шагом" << endl;
		cout << "5. Изменить количество цифр, которые нужно отсортировать" << endl;
		cout << "0. Выход" << endl;
		cin >> change;
		switch (change) {
		case 1: {
			cout << endl << "Сортировка методом простых вставок" << endl;
			cout << endl << "Сортировка неупорядоченного массива по возрастанию"
				<< endl;
			a.differentToUp();
			a.insertionSort();
			cout << endl << "Сортировка массива, упорядоченного по возрастанию, по возрастанию" << endl;
			a.insertionSort();
			cout << endl << "Сортировка массива, упорядоченного по убыванию, по возрастанию" << endl;
				a.upToDown();
			a.insertionSort();
			cout << "Запомните результаты. После нажания любой клавиши консоль очистится!" << endl;
				system("Pause");
			system("CLS");
			break;
		}
		case 2: {
			cout << endl << "Сортировка методом бинарных вставок" << endl;
			cout << endl << "Сортировка неупорядоченного массива по возрастанию"
				<< endl;
			a.differentToUp();
			a.sortArrayBinary();
			cout << endl << "Сортировка массива, упорядоченного по возрастанию, по возрастанию" << endl;
				a.sortArrayBinary();
			cout << endl << "Сортировка массива, упорядоченного по убыванию, по возрастанию" << endl;
				a.upToDown();
			a.sortArrayBinary();
			cout << "Запомните результаты. После нажания любой клавиши консоль очистится!" << endl;
				system("Pause");
			system("CLS");
			break;
		}
		case 3: {
			cout << endl << "Сортировка методом Шелла" << endl;
			cout << endl << "Сортировка неупорядоченного массива по возрастанию"<< endl;
			a.differentToUp();
			a.Shell();
			cout << endl << "Сортировка массива, упорядоченного по возрастанию, по возрастанию" << endl;
			a.Shell();
			cout << endl << "Сортировка массива, упорядоченного по убыванию, по возрастанию" << endl;
			a.upToDown();
			a.Shell();
			cout << "Запомните результаты. После нажания любой клавиши консоль очистится!" << endl;
			system("Pause");
			system("CLS");
			break;
		}
		case 4: {
			cout << endl << "Сортировка методом Шелла с другим шагом" << endl;
			cout << endl << "Сортировка неупорядоченного массива по возрастанию"<< endl;
			a.differentToUp();
			a.ShellSecond();
			cout << endl << "Сортировка массива, упорядоченного по возрастанию, по возрастанию" << endl;
			a.ShellSecond();
			cout << endl << "Сортировка массива, упорядоченного по убыванию, по возрастанию" << endl;
			a.upToDown();
			a.ShellSecond();
			cout << "Запомните результаты. После нажания любой клавиши консоль очистится!" << endl;
			system("Pause");
			system("CLS");
			break;
		}
		case 5: {
			cout << "Вы выбрали пункт: 'Изменить количество цифр' " << endl;
			sortAlgorithms* ptr = new sortAlgorithms(); //вызываем деструктор, для того, чтобы изменить количество чисел без потери памяти.
				ptr->~sortAlgorithms();
			a.choice();
			a.sortToDown();
			system("CLS");
			break;
		}
		}
	} while (change != 0);
	return 0;
}