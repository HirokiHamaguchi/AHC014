N = int(input())
rects = []
for i in range(N):
    As = list(input().split())
    assert(len(As) == 8)
    rects += "{"+",".join(As)+"},\n"

print()
print("{\n"+"".join(rects)+"}\n")
