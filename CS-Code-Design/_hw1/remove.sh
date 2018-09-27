# this script will remove all excutable files

files=$(ls *.c)
for i in $files
do
    rm ${i%*.c}
done