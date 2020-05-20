#include<iostream>
#include<stdio.h>
#include<fstream>
#include<chrono>
#include<unistd.h>
char directory_name_buff[80];
using namespace std;
int partition(long *arr, int s, int e)
{
	int start = arr[s];
	int end = arr[e];
//	int mid = arr[(s+e)/2];
	int pivot = arr[e];//_Median_(start, end, mid);
	int index_smaller = s - 1;
	
	for(int i = s; i<e; i++)
	{
		if(arr[i]<=pivot)
		{
			index_smaller++;
			swap(arr[index_smaller], arr[i]);
		}
	}
	swap(arr[index_smaller+1], arr[e]);
	return index_smaller+1;
	
}
void quick_sort(long *arr, int s, int e)
{
	if(s < e)
	{
		int index = partition(arr, s, e);
		quick_sort(arr, s, index-1);
		quick_sort(arr, index+1, e);	
	}
}
void merge(long *left, long *right, long *arr, int len_left, int len_right)
{
	int i=0, j=0, k=0;
	while(i<len_left && j<len_right)
	{
		if(left[i]<=right[j])
		{
			arr[k] = left[i];
			k++;
			i++;
		}
		else
		{
			arr[k] = right[j];
			k++;
			j++;
		}
	}
	while(i<len_left)
	{
		arr[k] = left[i];
		k++;
		i++;
	}
	while(j<len_right)
	{
		arr[k] = right[j];
		k++;
		j++;
	}
}
void quick_sort_helper(long *arr, int total)
{
	int end[4];
	end[0] = total/4;
	end[1] = total/4 + end[0];
	end[2] = total/4 + end[1];
	end[3] = total/4 + end[2];
	long *arr1 = new long[end[0]];
	long *arr2 = new long[end[0]];
	long *arr3 = new long[end[0]];
	long *arr4 = new long[end[0]];
	long *arr_temp1 = new long[end[1]];
	long *arr_temp2 = new long[end[1]];

	for(int i=0; i<end[0]; i++)
		arr1[i] = arr[i];
	for(int i=end[0]; i<end[1]; i++)
		arr2[i-end[0]] = arr[i];
	for(int i=end[1]; i<end[2]; i++)
		arr3[i-end[1]] = arr[i];
	for(int i=end[2]; i<end[3]; i++)
		arr4[i-end[2]] = arr[i];

	quick_sort(arr1, 0, end[0]-1);
	quick_sort(arr2, 0, end[0]-1);
	quick_sort(arr3, 0, end[0]-1);
	quick_sort(arr4, 0, end[0]-1);

	merge(arr1, arr2, arr_temp1, end[0], end[0]);
	merge(arr3, arr4, arr_temp2, end[0], end[0]);
	merge(arr_temp1, arr_temp2, arr, end[1], end[1]);
}
void save_log(string filename, string data, double elapsed_time)
{
	ofstream output(filename.c_str(), ios::app);
	if(!output)
	{
		cout<<"Couldn't open/create file!"<<endl;
		exit(1);
	}
	//output.seekp(0, ios::end);
	if(data == "Random_100000.txt")
	{
		output<<"Random 100000 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Random_100.txt")
	{
		output<<"Random 100 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Random_1000000.txt")
	{
		output<<"Random 1000000 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Random_Ascending.txt")
	{
		output<<"Ascending order sorted data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Random_Descending.txt")
	{
		output<<"Descending order sorted data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	output.close();
}
int main_helper(string data_set)
{
	auto start = chrono::high_resolution_clock::now();
	ifstream path("path.txt");
	string Data_Set_Path, Log;
	path>>Data_Set_Path;
	path>>Log;
	string file_input = Data_Set_Path+data_set;
	ifstream input(file_input.c_str());
	if(!input)
	{
		cout<<"Couldn't open file!"<<endl;
		exit(1);
	}
	int total=0;
	input>>total;
	long *input_arr = new long[total];
	for(int i=0; i<total; i++)
	{
		int number = 0;
		input>>number;
		input_arr[i] = number;
	}
	quick_sort_helper(input_arr, total);
	input.close();
	delete[] input_arr;
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	double elapsed_time = elapsed.count()*1000.0;
	save_log(Log+"Quick_Log(without_threading).txt", data_set, elapsed_time);
	return 0;
}
int main()
{
	string Data_Set[5] = {"Random_100.txt", "Random_100000.txt", "Random_1000000.txt", "Random_Ascending.txt", "Random_Descending.txt"};
	string mess[5] = {"Random 100 elements data set", "Random 100000 elements data set", "Random 1000000 elements data set", "Ascending order sorted data set", "Descending order sorted data set"};
	cout<<"Quick Sort"<<endl<<"With-out Threading"<<endl;
	for(int i=0; i<5; i++)
	{
		cout<<mess[i]<<endl<<endl;
		cout<<"Test#1\n";
		main_helper(Data_Set[i]);
		cout<<"Test#2\n";
		main_helper(Data_Set[i]);
		cout<<"Test#3\n\n";
		main_helper(Data_Set[i]);
	}
	return 0;
}
