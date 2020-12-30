import random

alphabet = "abcdefghijklmnopqrstuvwxyz"
random.seed(2)

la = list(alphabet)

fout = open("rplaces1.txt", "w")

for i in range(100):
    random.shuffle(la)
    x = "".join(la[:random.randint(6, 9)])
    print(x, file=fout)

fout.close()

fout = open("rplaces2.txt", "w")

for i in range(100):
    random.shuffle(la)
    x = "".join(la[:random.randint(6, 9)])
    print(x, file=fout)

fout.close()