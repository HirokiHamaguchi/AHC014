scores = dict()

with open("src/bash/bestScores.log", mode="r") as f:
    while True:
        s = f.readline()
        if s:
            seed, score = map(int, s.split("="))
            scores[seed] = score
        else:
            break
print(scores)
print(sum(scores.values()))
