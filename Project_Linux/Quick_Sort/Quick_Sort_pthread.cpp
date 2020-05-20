#include<iostream>
#include<stdio.h>
#include<fstream>
#include<chrono>
#include<unistd.h>
#include<pthread.h>
char directory_name_buff[80];
using namespace std;
struct Arguments
{
	long *array;
	int start;
	int end;
};
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
void *quick_sort(void *args)
{
	struct Arguments *args_ptr = (struct Arguments *) args;
	long *arr = args_ptr->array;
	int s = args_ptr->start;
	int e = args_ptr->end;
	if(s < e)
	{
		int index = partition(arr, s, e);
		struct Arguments temp[2];
		temp[0].array = arr;
		temp[0].start = s;
		temp[0].end = index-1;
		temp[1].array = arr;
		temp[1].start = index+1;
		temp[1].end = e;
		quick_sort((void *)&temp[0]);
		quick_sort((void *)&temp[1]);	
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
int quick_sort_helper(long *arr, int total)
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

	struct Arguments temp[4];
	temp[0].array = arr1;
	temp[0].start = 0;
	temp[0].end = end[0]-1;
	temp[1].array = arr2;
	temp[1].start = 0;
	temp[1].end = end[0]-1;
	temp[2].array = arr3;
	temp[2].start = 0;
	temp[2].end = end[0]-1;
	temp[3].array = arr4;
	temp[3].start = 0;
	temp[3].end = end[0]-1;

	pthread_t pid[4];
	int ret[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	ret[0] = pthread_create(&pid[0], &attr, quick_sort, &temp[0]);
	if(ret[0])
	{  
		  cout<<"Thread Creation Failed!\n";
		  return 0;
	}
	ret[1] = pthread_create(&pid[1], &attr, quick_sort, &temp[1]);
	if(ret[1])
	{  
		  cout<<"Thread Creation Failed!\n";
		  return 0;
	}
	ret[2] = pthread_create(&pid[2], &attr, quick_sort, &temp[2]);
	if(ret[2])
	{  
		  cout<<"Thread Creation Failed!\n";
		  return 0;
	}
	ret[3] = pthread_create(&pid[3], &attr, quick_sort, &temp[3]);
	if(ret[3])
	{  
		  cout<<"Thread Creation Failed!\n";
		  return 0;
	}
	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
	pthread_join(pid[2], NULL);
	pthread_join(pid[3], NULL);

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
	save_log("Quick_Log(pthread).txt", argv[3], elapsed_time);
	return 0;
}
