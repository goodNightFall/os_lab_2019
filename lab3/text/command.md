gcc find_min_max.c -o find_min_max 
gcc sequential_min_max.c -o sequential_min_max
gcc utils.c -o utils

gcc find_min_max.c sequential_min_max.c utils.c -o ./result 

gcc parallel_min_max.c find_min_max.c utils.c -o ./parallel_min_max

./parallel_min_max --seed 42 --array_size 10 --pnum 5 (тут pipe)
./parallel_min_max --seed 42 --array_size 10 --pnum 5 --by_files (создает файлы)