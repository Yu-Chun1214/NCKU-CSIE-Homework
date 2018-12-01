import re
import sys
import json
from os import system
from copy import copy

def main(file:str):
    rules={}
    for i in range(1,7):
        rules[i] = []
    with open(file,"r") as file:
        data = file.readlines()
        for i in data:
            i = i.rstrip('\n')
            temp = i.split(' ')
            temp[2] = temp[2] + temp[3] + temp[4]
            temp[5] = temp[5] + temp[6] + temp[7]
            del temp[3],temp[3],temp[4],temp[4]
            temp.append(temp[2] + temp[3] + temp[4])
            for i in range(0,6):
                rules[i + 1].append(copy(temp[i]))
        file.close()
    for i in range(1,6):
        print("F{}: {}".format(i,len(set(rules[i]))))
    print()
    ignore = ["@0.0.0.0/0","0.0.0.0/0","0:65535","0:65535","0x00/0x00"]
    for i in range(1,6):
        count = 0
        for j in rules[i]:
            if j == ignore[i - 1]:
                count += 1
        print("F{}: {}".format(i,count))
    print("\n",len(data),sep='')
    print("\n",len(set(rules[6])),sep='')

    pass

def data_process(data:list):
    pass

if __name__ == '__main__':
    file = sys.argv[1]
    main(file)