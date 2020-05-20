project_root=$(dirname $(dirname $(realpath $0 )))

clear
echo "Compiling and running Merge Sort"
echo ""
echo "OpenMP"
g++ -o $project_root/Merge_Sort/Merge_Sort_OMP $project_root/Merge_Sort/Merge_Sort_OMP.cpp -fopenmp

echo "Random 100 elements data set"
echo "Test#1"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_100.txt

echo "Test#2"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_100.txt

echo "Test#3"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_100.txt
echo ""

echo "Random 100000 elements data set"
echo "Test#1"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_100000.txt

echo "Test#2"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_100000.txt

echo "Test#3"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_100000.txt
echo ""

echo "Random 1000000 elements data set"
echo "Test#1"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_1000000.txt

echo "Test#2"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_1000000.txt

echo "Test#3"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_1000000.txt
echo ""

echo "Ascending order sorted data set"
echo "Test#1"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_Ascending.txt

echo "Test#2"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_Ascending.txt

echo "Test#3"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_Ascending.txt
echo ""

echo "Descending order sorted data set"
echo "Test#1"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_Descending.txt

echo "Test#2"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_Descending.txt

echo "Test#3"
$project_root/Merge_Sort/./Merge_Sort_OMP $project_root/Data_Set $project_root/Log Random_Descending.txt
echo ""
