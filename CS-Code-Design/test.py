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

def loadData(name:str) -> list:
    str_data = []
    int_data = []
    with open(name,'r') as file:
        data = file.read()
        str_data = data.split(' ')
        # print(str_data)
        # del str_data[len(str_data) - 1]
        for i in str_data:
            if(i != ''):
                try:
                    int_data.append(i)
                except ValueError as e:
                    print(i)
        # int_data = [int(i) for i in str_data if i is not '' or '\n']
        return int_data

def cmpr(data1,data2):
    # if len(data1) != len(data2) :
    #     raise Exception('Length is not the same data1 length is %d data2 length is %d' % (len(data1),len(data2)))
    current = 0
    for i in range(len(data1)):
        current += 1
        if(data1[i] != data2[i]):
            raise Exception('data Wrong data1 num %s and data2 num %s is not the same current is %d' % (data1[1],data2[i],current))
                
        
if __name__ == '__main__':
    filename1 = os.sys.argv[1]
    data1 = loadData(filename1)
    with open('file1.txt','w') as file:
        for i in data1:
            file.write(i+'\n')
    # os.system('pause')
    filename2 = os.sys.argv[2]
    data2 = loadData(filename2)
    with open('file2.txt','w') as file:
        for i in data2:
            file.write(i+'\n')
    # cmpr(data1,data2)