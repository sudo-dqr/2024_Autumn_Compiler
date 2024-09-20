cd submit
rm submit.zip
rm CMakeLists.txt
rm *.cpp
rm *.h
cp ../CMakeLists.txt ./CMakeLists.txt
cp ../src/*.cpp ./*.cpp
cp ../include/*.h ./*.h
zip submit.zip *