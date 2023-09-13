count=1
sum=0
while [ -n "$1" ]
do
    count=$[ $count + 1 ]
    sum=$[$1+$sum]
shift
done

count=$[ $count - 1 ]
aver=$[$sum/$count]


echo "Количество: $count"
echo "Среднее арифмитическое: $aver"
