#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<chrono>
#include<unistd.h>
#include<algorithm>
#include<omp.h>
#define NUM_THREADS 2
char directory_name_buff[80];
using namespace std;
void counting_sort(long *arr, int start, int size, int pow, int total)
{
	long *result = new long[total];
	int new_arr[10] = {0};
	for(int i=start; i<size; i++)
	{
		new_arr[(arr[i]/pow)%10]++;
	}
	//cumulative frenquency
	for(int i=1; i<10; i++)
	{
		new_arr[i] += new_arr[i-1];
	}
	//sorting
	for(int i=size-1; i>=start; i--)
	{
		result[new_arr[(arr[i]/pow)%10]-1] = arr[i];
		new_arr[(arr[i]/pow)%10]--;
	}
	int k=0;
	for(int i=start; i<size; i++)
		arr[i] = result[k++];
	delete[] result;
}
void radix_sort(long *arr, int start, int size, int max, int total)
{
	int pow = 1;
	while(max/pow != 0)
	{
		counting_sort(arr, start, size, pow, total);
		pow = pow*10;
	}
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
	if(data == "Radix_100000.txt")
	{
		output<<"Random 100000 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Radix_100.txt")
	{
		output<<"Random 100 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Radix_1000000.txt")
	{
		output<<"Random 1000000 data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Radix_Ascending.txt")
	{
		output<<"Ascending order sorted data set"<<endl;
		output<<"Time Elapsed: "<<elapsed_time<<"ms"<<endl<<endl;
	}
	else if(data == "Radix_Descending.txt")
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
	//Spliting data into two sections
	int _start[2], _end[2];
	_start[0] = 0;
	_end[0]=(total/2);
	_start[1] = (total/2);
	_end[1] = total;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				int id = omp_get_thread_num();
				int max = *max_element(input_arr+_start[0], input_arr+_end[0]);
				radix_sort(input_arr, _start[0], _end[0], max, _end[0]);
			}
			#pragma omp section
			{
				int id = omp_get_thread_num();
				int max = *max_element(input_arr+_start[1], input_arr+_end[1]);
				radix_sort(input_arr, _start[1], _end[1], max, _start[1]);
			}
		}
	}
	input.close();
	long *result_arr = new long[total];
	int i=_start[0], j=_start[1], k=0;
	while(i<_end[0] && j<_end[1])
	{
		if(input_arr[i]<=input_arr[j])
		{
			result_arr[k] = input_arr[i];
			k++;
			i++;
		}
		else
		{
			result_arr[k] = input_arr[j];
			k++;
			j++;
		}
	}
	while(i<_end[0])
	{
		result_arr[k] = input_arr[i];
		k++;
		i++;
	}
	while(j<_end[1])
	{
		result_arr[k] = input_arr[j];
		k++;
		j++;
	}
	delete[] result_arr;
	delete[] input_arr;
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	double elapsed_time = elapsed.count()*1000;
	save_log(Log+"Radix_Log(OMP).txt", data_set, elapsed_time);
	return 0;
}
int main()
{
	string Data_Set[5] = {"Radix_100.txt", "Radix_100000.txt", "Radix_1000000.txt", "Radix_Ascending.txt", "Radix_Descending.txt"};
	string mess[5] = {"Random 100 elements data set", "Random 100000 elements data set", "Random 1000000 elements data set", "Ascending order sorted data set", "Descending order sorted data set"};
	cout<<"Radix Sort"<<endl<<"OpenMP"<<endl;
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
