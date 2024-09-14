rm ./submit/testfile*

cp ./src/*.c ./submit/

for i in 1 2 3 4 5 6
do 
    mv ./submit/testfile$i.c ./submit/testfile$i.txt
done    

for i in 1 2 3 4 5 6
do
    ./src/testfile$i > ./submit/output$i.txt
done    

for i in 1 2 3 4 5 6
do 
    rm ./src/testfile$i
done