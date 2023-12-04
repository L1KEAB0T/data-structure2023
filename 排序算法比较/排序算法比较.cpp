#include<iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#define MAX_NUM 50000

int getRand(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}
void swap(int& a, int& b) {
	int c;
	c = a;
	a = b;
	b = c;
}
void Bubble_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(-MAX_NUM, MAX_NUM);
	}
	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	for (int i = 0; i < n; i++)
		for (int j = n; j > i; j--) {
			Compare_Num++;
			if (num[j] > num[j - 1]) {
				Swap_Num++;
				swap(num[j], num[j - 1]);
			}
		}
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
void Selection_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(-MAX_NUM, MAX_NUM);
	}
	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	int max, maxpos;
	for (int i = 0; i < n; i++) {
		max = num[i];
		maxpos = i;
		for (int j = n; j > i; j--) {
			Compare_Num++;
			if (num[j] > max) {
				max = num[j];
				maxpos = j;
			}
		}
		if (maxpos != i) {
			Swap_Num++;
			swap(num[i], num[maxpos]);
		}
	}
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
void Insert_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(-MAX_NUM, MAX_NUM);
	}

	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;

	for (int i = 1; i < n; i++) {
		int key = num[i];
		int j = i - 1;

		Compare_Num++;
		while (j >= 0 && num[j] < key) {
			Swap_Num++;
			num[j + 1] = num[j];
			j--;
		}

		num[j + 1] = key;
		Swap_Num++;
	}
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
void Shell_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(-MAX_NUM, MAX_NUM);
	}

	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	int gap = n / 2; // 初始步长设为数组长度的一半

	while (gap > 0) {
		for (int i = gap; i < n; i++) {
			int temp = num[i];
			int j = i;

			Compare_Num++;
			while (j >= gap && num[j - gap] > temp) {
				Swap_Num++;
				num[j] = num[j - gap];
				j -= gap;
			}

			num[j] = temp;
		}

		gap /= 2; // 缩小步长
	}

	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
void quicksort(int num[], int start, int end, int& Swap_Num, int& Compare_Num) {
	if (start < end) {
		int base = num[start];
		int left = start;
		int right = end;
		while (left < right) {
			Compare_Num++;
			while (left < right && num[right] >= base) {
				right--;
			}
			Swap_Num++;
			num[left] = num[right];
			Compare_Num++;
			while (left < right && num[left] <= base) {
				left++;
			}
			Swap_Num++;
			num[right] = num[left];
		}
		Swap_Num++;
		num[left] = base;
		quicksort(num, start, left - 1, Swap_Num, Compare_Num);
		quicksort(num, left + 1, end, Swap_Num, Compare_Num);
	}
}
void Quick_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(-MAX_NUM, MAX_NUM);
	}

	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	quicksort(num, 0, n - 1, Swap_Num, Compare_Num);
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
void max_heapify(int arr[], int start, int end, int& Swap_Num, int& Compare_Num) {
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		Compare_Num++;
		if (son + 1 <= end && arr[son] < arr[son + 1])
			son++;
		Compare_Num++;
		if (arr[dad] > arr[son])
			return;
		else {
			Swap_Num++;
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}
void Heap_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(-MAX_NUM, MAX_NUM);
	}

	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	for (int i = n / 2 - 1; i >= 0; i--)
		max_heapify(num, i, n - 1, Swap_Num, Compare_Num);
	for (int i = n - 1; i > 0; i--) {
		Swap_Num++;
		swap(num[0], num[i]);
		max_heapify(num, 0, i - 1, Swap_Num, Compare_Num);
	}
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
void Merge_Sort(int n) {
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = getRand(-MAX_NUM, MAX_NUM);
	}

	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	int* a = arr;
	int* b = new int[n];
	for (int seg = 1; seg < n; seg += seg) {
		for (int start = 0; start < n; start += seg + seg) {
			int low = start, mid = min(start + seg, n), high = min(start + seg + seg, n);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2) {
				Compare_Num++;
				Swap_Num++;
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			}
			while (start1 < end1) {
				Swap_Num++;
				b[k++] = a[start1++];
			}
			while (start2 < end2) {
				Swap_Num++;
				b[k++] = a[start2++];
			}
		}
		int* temp = a;
		a = b;
		b = temp;
	}

	if (a != arr) {
		for (int i = 0; i < n; i++)
			b[i] = a[i];
		b = a;
	}
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] arr;
	delete[] b;
}
int getMax(int array[], int n) {
	int max = array[0];
	for (int i = 1; i < n; i++)
		if (array[i] > max)
			max = array[i];
	return max;
}

void countingSort(int array[], int size, int place) {
	const int max = 10;
	int* output = new int[size];
	int* count = new int[max];

	for (int i = 0; i < max; ++i)
		count[i] = 0;

	for (int i = 0; i < size; i++)
		count[(array[i] / place) % 10]++;

	for (int i = 1; i < max; i++)
		count[i] += count[i - 1];

	for (int i = size - 1; i >= 0; i--) {
		output[count[(array[i] / place) % 10] - 1] = array[i];
		count[(array[i] / place) % 10]--;
	}

	for (int i = 0; i < size; i++)
		array[i] = output[i];
}
void radixsort(int array[], int size) {
	int max = getMax(array, size);
	for (int place = 1; max / place > 0; place *= 10)
		countingSort(array, size, place);
}
void Radix_Sort(int n) {
	int* num = new int[n];
	for (int i = 0; i < n; i++) {
		num[i] = getRand(0, MAX_NUM);
	}
	clock_t start_time = clock();
	int Swap_Num = 0, Compare_Num = 0;
	radixsort(num, n);
	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "比较次数为" << Compare_Num << endl;
	cout << "交换次数为" << Swap_Num << endl;
	cout << "用时: " << duration << " seconds." << endl;
	delete[] num;
}
int main() {
	int n;
	srand(time(0));
	cout << "输入产生随机数的个数:";
	cin >> n;
	while (!(n > 0 && n <= MAX_NUM)) {
		cout << "n输入错误,请重新输入:";
		cin >> n;
	}
	while (true) {
		cout << "\n选择排序算法：\n";
		cout << "1. 冒泡排序\n";
		cout << "2. 选择排序\n";
		cout << "3. 直接插入排序\n";
		cout << "4. 希尔排序\n";
		cout << "5. 快速排序\n";
		cout << "6. 归并排序\n";
		cout << "7. 堆排序\n";
		cout << "8. 基数排序\n";
		cout << "0. 退出\n";
		cout << "请输入选择 (0-8): ";

		int choice;
		cin >> choice;

		if (choice == 0) {
			cout << "退出程序。\n";
			break;
		}

		switch (choice) {
			case 1:
				Bubble_Sort(n);
				break;
			case 2:
				Selection_Sort(n);
				break;
			case 3:
				Insert_Sort(n);
				break;
			case 4:
				Shell_Sort(n);
				break;
			case 5:
				Quick_Sort(n);
				break;
			case 6:
				Merge_Sort(n);
				break;
			case 7:
				Heap_Sort(n);
				break;
			case 8:
				Radix_Sort(n);
				break;
			default:
				cout << "无效的选择，请重新输入。\n";
				continue;
		}

	}
	//Bubble_Sort(n);
	//Selection_Sort(n);
	//Insert_Sort(n);
	//Shell_Sort(n);
	//Quick_Sort(n);
	//Heap_Sort(n);
	//Merge_Sort(n);
	//Radix_Sort(n);
	return 0;
}