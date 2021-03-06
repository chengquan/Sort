// sort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
void quick_sort(vector<int> &data, int m, int n);
void bubble_sort(vector<int> &data);
void select_sort(vector<int> &data);
void insert_sort(vector<int> &data);
void shell_sort(vector<int> &data);
void Merge_sort(vector<int> &data, int l, int r);
void Merge(vector<int> &data, int l, int r);
void heap_sort(vector<int> &data);
void MaxHeapFixDown(vector<int> &data, int i, int n);
void Count_sort(vector<int> &data);
void Bucket_sort(vector<int> &data);
void Radix_sort(vector<int> &data);



int main()
{
	vector<int> data = {7,5,13,19,24,1,11,23,4,2,17,23,6,7,12,53};
	//bubble_sort(data);
	//select_sort(data);
	//insert_sort(data);
	//shell_sort(data);
    //Merge_sort(data, 0, 15);
	//quick_sort(data, 0, 15);
	//Count_sort(data);
	//Radix_sort(data);
	//Bucket_sort(data);
	heap_sort(data);
    return 0;
}



//冒泡排序
void bubble_sort(vector<int> &data)
{
	bool ok = true;
	int i,j,t = 0;
	for (int i = 1; i < data.size(); i++)
	{
		ok = true;
		for (int j = 1; j < data.size()-i+1; j++)
		{
			if (data[j] < data[j - 1])
			{
				t = data[j];
				data[j] = data[j - 1];
				data[j - 1] = t;
				ok = false;
			}
		}
		if (ok)
			break;
	}

}

//选择排序(最小的交换)
void select_sort(vector<int> &data)
{
	int min = data[0],t=0,x=0;
	for (int j = 1; j < data.size(); j++)
	{
		for (int i = j; i < data.size(); i++)
		{
			if (data[i] < min)
			{
				min = data[i];
				t = i;
			}
		}
		x = data[j - 1];
		data[j - 1] = min;
		data[t] = x;
		min = data[j];
	}
}

//插入排序
void insert_sort(vector<int> &data)
{
	int t;
	for (int j = 0; j < data.size(); j++)
	{
		for (int i = j; i > 0; i--)
		{
			if (data[i] < data[i - 1])
			{
				t = data[i];
				data[i] = data[i - 1];
				data[i - 1] = t;
			}
		}
	}
}


//希尔排序
void shell_sort(vector<int> &data)
{
	int gen = data.size()/3;
	int t,j;
	for(gen;gen>0;gen=(gen+1)/3)
		for (int i = gen; i < data.size(); i++)
		{
			t = data[i];
			for (j = i - gen; j >= 0 && data[j] > t; j -= gen)
			{
				data[j + gen] = data[j];
			}
			data[j + gen] = t;

		}
}

//归并排序
void Merge_sort(vector<int> &data,int l,int r)
{
	if (r - l == 1)
	{
		if (data[l] > data[r])
		{
			int t = data[l];
			data[l] = data[r];
			data[r] = t;
		}
		return;
	}else if (r - l == 0)
		return;
	else
	{
		int mid = (r - l + 1) / 2;
		Merge_sort(data, l, l + mid);
		Merge_sort(data, l + mid + 1, r);
		Merge(data, l, r);
	}

}

void Merge(vector<int> &data, int l, int r)
{
	vector<int> ss;
	int mid = (r - l + 1) / 2;
	int left_index = l;
	int right_index = l + mid + 1;
	while (left_index < l + mid + 1 && right_index < r + 1)
	{
		if (data[left_index] <= data[right_index])
			ss.push_back(data[left_index++]);
		else
			ss.push_back(data[right_index++]);
	}
	while (left_index < l + mid + 1)ss.push_back(data[left_index++]);
	while (right_index < r + 1)ss.push_back(data[right_index++]);
	for (int i = 0; i < r - l + 1; i++)
	{
		data[i + l] = ss[i];
	}
}



//快速排序
void quick_sort(vector<int> &data,int m ,int n)
{
	int i = m, j = n + 1, k = 0, x = 0;;
	if (m < n)
	{
		k = data[m];
		while (i < j)
		{
			for (i = i + 1; i < n; i++)
			{
				if (data[i] > k)
				break;
			}
			for (j = j - 1; j > m; j--)
			{
				if (data[j] < k)
				break;
			}
			if (i < j)
			{
				x = data[i];
				data[i] = data[j];
				data[j] = x;
			}
		}
			x = data[j];
			data[j] = data[m];
			data[m] = x;
			quick_sort(data, m, j - 1);
			quick_sort(data, j + 1, n);
		

	}
}

//堆排序
void heap_sort(vector<int> &data)
{
	 int n = data.size();
	  for (int i = n / 2 - 1; i >= 0; i--)
	         MaxHeapFixDown(data, i, n);
	  for (int i = n - 1; i >= 1; i--) {
	         swap(data[i], data[0]);
		     MaxHeapFixDown(data, 0, i);
	}

}

void MaxHeapFixDown(vector<int> &data, int i, int n) {
	     int j = 2 * i + 1;
	    int temp = data[i];
	    while (j<n)
		{
		   if (j + 1<n&&data[j]<data[j + 1])
		          ++j;
	       if (temp>data[j])
		        break;
		   else 
		   {
				data[i] = data[j];
		        i = j;
                j = 2 * i + 1;
			
			}
		}
		data[i] = temp;
}

//计数排序
void Count_sort(vector<int> &data)
{
	map<int, int> ss;
	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
		ss[*iter]++;
	}
	int i = 0;
	for (auto it = ss.begin(); it != ss.end(); it++)
	{
		for (int j = 0; j < it->second; j++)
		{
			data[i] = it->first;
			i++;
		}
	}
}

////桶排序
void Bucket_sort(vector<int> &data)
{
	vector<vector<int>> ss(10);
	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
		int j = *iter / 10;
		ss[j].push_back(*iter);
	}
	int x = 0;
	for (auto iter = ss.begin(); iter != ss.end(); iter++)
	{
		bubble_sort(*iter);
		for (auto it = iter->begin(); it != iter->end(); it++)
		{
			data[x] = *it;
			x++;
		}
	}

	
}

//基数排序
void Radix_sort(vector<int> &data)
{
	vector<vector<int>> ss(10);
	int x = 0;
	for (int i = 0; i < 2; i++)
	{
		for (auto iter = data.begin(); iter != data.end(); iter++)
		{
			int j;
			if(i==0)j = *iter % 10;
			else j = *iter / 10;
			ss[j].push_back(*iter);
		}
		 x = 0;
		for (auto iter = ss.begin(); iter != ss.end(); iter++)
		{
			for (auto it = iter->begin(); it != iter->end(); it++)
			{
				data[x] = *it;
				x++;
			}
		}
		for (int i = 0; i < 10; i++)
			ss[i].clear();
	}
}




