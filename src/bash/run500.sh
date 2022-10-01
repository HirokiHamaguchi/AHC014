set -e

echo "now compiling..."
/usr/bin/g++ -fdiagnostics-color=always ./src/cpp/solve.cpp -o ./src/cpp/solve -std=c++17 -Wall -Wextra -O3 -DTEST

YELLOW="\033[33m"
RESET="\033[0m"
FOLDER="./src/bash/"
F_OUT="${FOLDER}out500.log"

seedNum=49 #500-1

echo -n >| $F_OUT

TIMEFORMAT=$' | time:%3lR'

declare -A nowScores
for seed in $(seq -f '%04g' 342 $seedNum); do
    echo "seed:$seed"
    echo "seed:$seed" >> $F_OUT
    time { score=$(./src/cpp/solve < input2/$seed.txt 2> /dev/null); }
    echo " |score:$score"
    echo " |score:$score" >> $F_OUT
    nowScores[$seed]=$score
done

avg=0
for score in ${nowScores[@]}; do
   ((avg+=score))
done
echo avg: $avg
echo avg: $avg >> $F_OUT
