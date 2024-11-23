cd ../submit
rm submit.zip
rm *.cpp
rm *.h
cp ../src/frontend/*.cpp ./
cp ../src/llvm/*.cpp ./
cp ../include/frontend/*.h ./
cp ../include/llvm/*.h ./
zip submit.zip *