#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<chrono>
#include<unistd.h>
#include<algorithm>
#include<pthread.h>
char directory_name_buff[80];
using namespace std;
struct Arguments
{
	long *array;
	int _start;
	int _size;
	int _max;
	int _total;
};
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
void *radix_sort(void *args)
{
	struct Arguments *args_ptr = (struct Arguments *) args;
	long *arr = args_ptr->array;
	int start = args_ptr->_start;
	int size = args_ptr->_size;
	int max = args_ptr->_max;
	int total = args_ptr->_total;
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
		//Spliting data into two sections
		int start[2], end[2];
		int max[2];
		int ret[2];
		start[0] = 0;
		end[0]=(total/2);
		start[1] = (total/2);
		end[1] = total;
		max[0] = *max_element(input_arr+start[0], input_arr+end[0]);
		max[1] = *max_element(input_arr+start[1], input_arr+end[1]);

		struct Arguments temp[2];
		temp[0].array = input_arr;
		temp[0]._start = start[0];
		temp[0]._size = end[0];
		temp[0]._max = max[0];
		temp[0]._total = end[0];

		temp[1].array = input_arr;
		temp[1]._start = start[1];
		temp[1]._size = end[1];
		temp[1]._max = max[1];
		temp[1]._total = start[1];

		pthread_t pid[2];
		pthread_attr_t attr;
	        pthread_attr_init(&attr);
		pthread_create(&pid[0], &attr, radix_sort, &temp[0]);
		if(ret[0])
		{  
			  cout<<"Thread Creation Failed!\n";
			  return 0;
		}
		pthread_create(&pid[1], &attr, radix_sort, &temp[1]);
		if(ret[1])
		{  
			  cout<<"Thread Creation Failed!\n";
			  return 0;
		}
		pthread_join(pid[0], NULL);
		pthread_join(pid[1], NULL);
		input.close();
		long *result_arr = new long[total];
		int i=start[0], j=start[1], k=0;
		while(i<end[0] && j<end[1])
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
		while(i<end[0])
		{
			result_arr[k] = input_arr[i];
			k++;
			i++;
		}
		while(j<end[1])
		{
			result_arr[k] = input_arr[j];
			k++;
			j++;
		}
		delete[] result_arr;
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
	save_log("Radix_Log(pthread).txt", argv[3], elapsed_time);
	return 0;
}
