set -e

echo "now compiling..."
/usr/bin/g++ -fdiagnostics-color=always ./src/cpp/solve.cpp -o ./src/cpp/solve -std=c++17 -Dhari64 -Wall -Wextra -O3

./src/cpp/solve < input/0001.txt
