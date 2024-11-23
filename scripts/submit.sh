cd ../submit
rm submit.zip
rm *.cpp
rm *.h
rm -rf ./include
rm -rf ./src
rm CMakeLists.txt
cp ../include ./ -r
cp ../src ./ -r
cp ../CMakeLists.txt ./
zip -r submit.zip *