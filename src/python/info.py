outfile_path = "inputInfo/50.md"

scores = dict()
with open("src/bash/bestScores.log", mode="r") as f:
    while True:
        s = f.readline()
        if s:
            seed, score = map(int, s.split("="))
            scores[seed] = score
        else:
            break

with open(outfile_path, mode="w") as outfile:
    print("# INFO_50", file=outfile)
    print("", file=outfile)
    print("| seed | N   | M   | N*N/M | score   |", file=outfile)
    print("| ---- | --- | --- | ----- | ------- |", file=outfile)
    for seed in range(50):
        with open(f"input/{seed:04}.txt", mode="r") as f:
            N, M = map(int, f.readline().split())
            print(
                f"| {seed:<4} | {N:<3} | {M:<3} | {N*N/M:<5.2f} | {scores[seed]:<7} |", file=outfile)
