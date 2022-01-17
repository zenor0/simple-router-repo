#include <stdio.h>
#include <stdlib.h>
void BubbleSort(int numArray[], int numCount);
void SelectSort(int numArray[], int numCount);
void IntSwap(int *a, int *b);
void insertion_sort(int* a, int n);

int main(void)	//test driver
{
	int arr[5] = {7, 8, 3, 4, 9};


	//insertion_sort(arr, 5);
	
	//compare need to start at the begining of the array
	
	//pick up an element
	//store it into a varible "key"
	
	//Compare
		//begin at the former element of "key"
		//once reach to the start or find the correct place
		//stop the compare and insert
	
	
	for (int i = 0; i < 5; ++i)
	{
		int key = arr[i];
		
		int cmpIndex = i - 1;
		
		while (cmpIndex > 0 && arr[cmpIndex] > key)
		{
			arr[cmpIndex] = arr[cmpIndex + 1];
		}
	}



	//output
	for (int i = 0; i < 5; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}
//用指针实现元素交换
void IntSwap(int *a, int *b)	//传入两个int类型的指针(内存地址)
{
	int temp = *a;	//新建变量temp, 使用解引用符* 获取指针a指向的int变量内容 存入变量temp
	*a = *b;	//解引用指针a所指向的内存, 将其赋值为指针b指向的内容
	*b = temp;	//解引用指针b所指向的内存, 将其赋值为temp

}
//bubble sort
void BubbleSort(int numArray[], int numCount)
{
	for (int i = 0; i < numCount; i++)
	{
		for (int j = 1; j < numCount; j++)
		{
			if (numArray[j - 1] > numArray[j])
			{
				IntSwap(&numArray[j - 1], &numArray[j]);
			}
		}
	}
}
//selecct sort
void SelectSort(int numArray[], int numCount)
{
	int min, minIndex;
	for (int i = 0; i < numCount; i++)
	{
		min = numArray[i];
		minIndex = i;
		//find minimum value
		for (int j = i + 1; j < numCount; j++)
		{
			if (numArray[j] < min)
			{
				min = numArray[j];
				minIndex = j;
			}
		}
		IntSwap(&numArray[i], &numArray[minIndex]);
	}
}

//insert sort
void InsertSort(int arr[], int numCount)
{

}
//pick one element

//compare one by one

//insert and move other elements backwards

//loop


