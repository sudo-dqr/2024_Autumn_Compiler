cd submit
rm submit.zip
rm CMakeLists.txt
rm *.cpp
rm *.h
cp ../CMakeLists.txt ./CMakeLists.txts
cp ../src/*.cpp ./
cp ../include/*.h ./
zip submit.zip *