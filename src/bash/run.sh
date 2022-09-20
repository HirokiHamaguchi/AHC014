set -e

echo "now compiling..."
/usr/bin/g++ -fdiagnostics-color=always ./src/cpp/solve.cpp -o ./src/cpp/solve -std=c++17 -Dhari64 -Wall -Wextra -O3

YELLOW="\033[33m"
RESET="\033[0m"
read -p "$(echo -e $YELLOW"seed: "$RESET)" seed
seed=$(( seed ? seed : 0 ))
seed=`printf "%04d\n" "${seed}"`
./src/cpp/solve < input/${seed}.txt