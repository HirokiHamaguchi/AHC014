set -e

echo "now compiling..."
/usr/bin/g++ -fdiagnostics-color=always ./src/cpp/solve.cpp -o ./src/cpp/solve -std=c++17 -Wall -Wextra -O3 -DTEST

YELLOW="\033[33m"
RESET="\033[0m"
FOLDER="./src/bash/"
F_OUT="${FOLDER}out.log"
F_BESTSCORES="${FOLDER}bestScores.log"

seedNum=0049 #50-1

echo -n >| $F_OUT

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

declare -A nowScores
for seed in $(seq -f '%04g' 0 $seedNum); do
    echo "seed:$seed"
    time { score=$(./src/cpp/solve < input/$seed.txt 2> output/$seed.txt); }
    prev="${prevScores[${seed}]}"
    if [ $prev != "" ]; then
        percent=`python3 -c "print($score/$prev*100)"`%
    else
        percent="no prev"
    fi
    echo " |score:$score ($percent)"
    echo $seed=$score >> $F_OUT
    nowScores[$seed]=$score
done

avg=0
for score in ${nowScores[@]}; do
   ((avg+=score))
done
echo avg: $avg

echo -n >| $F_BESTSCORES

for seed in $(seq -f '%04g' 0 $seedNum); do
    prev=${prevScores[${seed}]}
    now=${nowScores[${seed}]}
    score=$(( prev > now ? prev : now ))
    echo $seed=$score >> $F_BESTSCORES
done