import sys
import queue


def generateDesign(P):
    design = []
    i = 0
    while (P > 0):
        if P & (i + 1) != 0:
            design.append(i)
            P = (P & ~(i + 1))
        i += 1
    return design


def generateKey(value, length):
    key = []
    i = 1
    while (value >= i):
        if (value & i != 0):
            key.append(1)
        else:
            key.append(0)
        value = (value & ~(i + 1))
        i = i << 1
    if len(key) < length:
        for i in range(length - len(key)):
            key.append(0)
    return key


def pulse(lfsr, design):
    # lfsr ist gedreht!
    v = lfsr[design[0]]
    for i in design[1:]:
        v = v ^ lfsr[i]
    lfsr.append(v)
    return lfsr.popleft()


if len(sys.argv) != 4:
    print('Not enough arguments')
    exit()

nlfsr = 4
P = int(sys.argv[1])
K = int(sys.argv[2])
N = int(sys.argv[3])

design = generateDesign(P)
print("P = " + str(P) + " = " + str(design))

key = generateKey(K, nlfsr)
print("K = "+ str(K) + " = " + str(key))

lfsr = queue.deque(key)
result = []

for x in range(N):
    result.append(pulse(lfsr, design))

print(result)
