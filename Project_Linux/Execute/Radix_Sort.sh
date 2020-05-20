project_root=$(dirname $(dirname $(realpath $0 )))

clear
echo "Compiling and running Radix Sort"
echo ""
echo "With-out Threading"
g++ -o $project_root/Radix_Sort/Radix_Sort $project_root/Radix_Sort/Radix_Sort.cpp

echo "Random 100 elements data set"
echo "Test#1"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_100.txt

echo "Test#2"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_100.txt

echo "Test#3"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_100.txt
echo ""

echo "Random 100000 elements data set"
echo "Test#1"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_100000.txt

echo "Test#2"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_100000.txt

echo "Test#3"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_100000.txt
echo ""

echo "Random 1000000 elements data set"
echo "Test#1"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_1000000.txt

echo "Test#2"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_1000000.txt

echo "Test#3"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_1000000.txt
echo ""

echo "Ascending order sorted data set"
echo "Test#1"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_Ascending.txt

echo "Test#2"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_Ascending.txt

echo "Test#3"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_Ascending.txt
echo ""

echo "Descending order sorted data set"
echo "Test#1"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_Descending.txt

echo "Test#2"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_Descending.txt

echo "Test#3"
$project_root/Radix_Sort/./Radix_Sort $project_root/Data_Set $project_root/Log Radix_Descending.txt
echo ""
