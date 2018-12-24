import os
import random

def check():
    with open('result.txt','r') as f:
        a = f.read()
        str_result = a.split(' ')
        del str_result[len(str_result) - 1]
        for i in range(len(str_result) - 1):
            if(int(str_result[i]) < int(str_result[i + 1])):
                print(str_result[i],str_result[i + 1])
                raise Exception('Wrong Result!')
        
if __name__ == '__main__':
    # rnd = random.randint(0,1000)
    rnd = 100000
    os.system('icc -std=c99 hw8.c')
    os.system('./a.out %d > result.txt' % rnd)
    check()