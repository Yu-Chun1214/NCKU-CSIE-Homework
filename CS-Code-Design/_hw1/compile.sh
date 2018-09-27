files=$(ls *.c)
for i in $files
do
    gcc -o ${i%*.c} $i
done
# for i in $(ls *.c)
# do
#     echo $i
# done
