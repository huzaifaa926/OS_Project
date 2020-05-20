#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<chrono>
#include<unistd.h>
#include<algorithm>
char directory_name_buff[80];
using namespace std;
void counting_sort(long *arr, int size, int pow)
{
	long *result = new long[size];
	int new_arr[10] = {0};
	for(int i=0; i<size; i++)
	{
		new_arr[(arr[i]/pow)%10]++;
	}
	//cumulative frenquency
	for(int i=1; i<10; i++)
	{
		new_arr[i] += new_arr[i-1];
	}
	//sorting
	for(int i=size-1; i>=0; i--)
	{
		result[new_arr[(arr[i]/pow)%10]-1] = arr[i];
		new_arr[(arr[i]/pow)%10]--;
	}
	for(int i=0; i<size; i++)
		arr[i] = result[i];
}
void radix_sort(long *arr, int size, int max)
{
	int pow = 1;
	while(max/pow != 0)
	{
		counting_sort(arr, size, pow);
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
	int max = *max_element(input_arr, input_arr+total);
	radix_sort(input_arr, total, max);
	input.close();
	delete[] input_arr;
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	double elapsed_time = elapsed.count()*1000;
	save_log(Log+"Radix_Log(without_threading).txt", data_set, elapsed_time);
	return 0;
}
int main()
{
	string Data_Set[5] = {"Radix_100.txt", "Radix_100000.txt", "Radix_1000000.txt", "Radix_Ascending.txt", "Radix_Descending.txt"};
	string mess[5] = {"Random 100 elements data set", "Random 100000 elements data set", "Random 1000000 elements data set", "Ascending order sorted data set", "Descending order sorted data set"};
	cout<<"Radix Sort"<<endl<<"With-out Threading"<<endl;
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
