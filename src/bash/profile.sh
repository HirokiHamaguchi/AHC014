echo "now compiling..."
/usr/bin/g++ -pg -g -fdiagnostics-color=always ./src/cpp/solve.cpp -o ./src/cpp/solve -std=c++17 -Wall -Wextra -O3
echo "now running..."
./src/cpp/solve < input/0004.txt
gprof ./src/cpp/solve gmon.out # -A
rm gmon.out