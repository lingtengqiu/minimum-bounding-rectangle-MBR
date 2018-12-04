build:
		g++ -o process.so -shared -fPIC process.cpp
do:
		bash do.sh 4 ./label ./xml_files
