#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include<chrono>
char directory_name_buff[80];
using namespace std;
void merge(long*, long*, long*, int, int);
void merge_sort(long *arr, int size)
{
	if (size<2)
	 return;
	int mid = size/2;
	long *left = new long[mid];
	long *right = new long[size-mid];
	for(int i=0; i<mid; i++)
	{
		left[i] = arr[i];
	}
	for(int i=mid; i<size; i++)
	{
		right[i-mid] = arr[i];
	}
	merge_sort(left, mid);
	merge_sort(right, size-mid);
	merge(left, right, arr, mid, size-mid);
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
void merge_sort_helper(long *arr, int total)
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

	merge_sort(arr1, end[0]);
	merge_sort(arr2, end[0]);
	merge_sort(arr3, end[0]);
	merge_sort(arr4, end[0]);
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
	else if(data == "Random_1000000.txt")
	{
		output<<"Random 1000000 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Random_100.txt")
	{
		output<<"Random 100 data set"<<endl;
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
int main(int argcnt, char *argv[])
{
	auto start = chrono::high_resolution_clock::now();
	if(argcnt == 4)
	{
		getcwd(directory_name_buff, sizeof directory_name_buff);
		if(chdir(argv[1]))
		{
			cout<<"Directory Couldn't be change!";
			exit(1);
		}
		string file_input = argv[3];
		ifstream input(file_input.c_str());
		if(!input.is_open())
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
		merge_sort_helper(input_arr, total);
		input.close();
		delete[] input_arr;
	}
	else
	{
		cout<<"No input file found!\n";
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	double elapsed_time = elapsed.count()*1000;
	if(chdir(argv[2]))
	{
		cout<<"Directory Couldn't be change!";
		exit(1);
	}
	save_log("Merge_Log(without_threading).txt", argv[3] ,elapsed_time);
	return 0;
}
