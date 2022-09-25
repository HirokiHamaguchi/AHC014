set -e

seedNum=0049 #50-1

for seed in $(seq -f '%04g' 0 $seedNum); do
    echo "seed:$seed"
    ./tools/target/release/vis $seed ./input/$seed.txt ./output/$seed.txt 1
done
