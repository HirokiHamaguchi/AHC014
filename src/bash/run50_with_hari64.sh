set -e

echo "now compiling..."
/usr/bin/g++ -fdiagnostics-color=always ./src/cpp/solve.cpp -o ./src/cpp/solve -std=c++17 -Wall -Wextra -O3 -Dhari64

YELLOW="\033[33m"
RESET="\033[0m"
FOLDER="./src/bash/"
F_BESTSCORES="${FOLDER}bestScores.log"

seedNum=0049 #50-1

declare -A prevScores
if [ -f $F_BESTSCORES ]; then
    IFS==
    while read line; do
        ARR=($line)
        prevScores[${ARR[0]}]=${ARR[1]}
    done < $F_BESTSCORES
    IFS=$'\n'
fi

TIMEFORMAT=$' | time:%3lR'

for seed in $(seq -f '%04g' 0 $seedNum); do
    echo "seed:$seed"
    ./src/cpp/solve < input/$seed.txt > output/$seed.txt
    prev="${prevScores[${seed}]}"
    echo " |score:$score ($prev)"
done
