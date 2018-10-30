import json
import random
import copy
from os import system
from subprocess import check_output
from threading import Thread
from multiprocessing import Process
from test import TestDouble,TestFloat

def lunch(process:str,pattern:str,result,mode):
    test_result = check_output('./{} {} {}'.format(process,mode,pattern),shell=True)
    try:
        result.append(json.loads(test_result.decode('utf-8').rstrip('\n')))
    except:
        print(result)
    # print(json.dumps(result,indent=4))
def Test_x32():
    i = 0
    failed_test = []
    while i < 10 :
        if i % 2 == 0:
            ans = TestFloat(num=random.randint(-2147483648,2147483647),NumToString=False)
            pass
        else:
            ans = TestFloat(num=round(random.uniform(-2147483648,2147483647)/100,8),NumToString=False)
            pass
        result_C = []
        result_P = []
        threads = []
        threads.append(Thread(target=lunch,args=('testC',ans[1],result_C,1)))
        threads.append(Thread(target=lunch,args=('testP',ans[1],result_P,1)))
        # lunch('testC',ans[1],result_C,1)
        # lunch('testP',ans[1],result_P,1)
        # print(json.dumps(result_C,indent=4))
        for thread in threads:
            thread.start()

        for thread in threads:
            thread.join()

        if ans[0] == float(result_C[0]["float"]) == float(result_P[0]['float']) and int(result_C[0]['integer']) == int(result_P[0]['integer']):
            pass
        else:
            failed_test.append({
                "test bitpattern" : ans[1],
                "Ans Float":ans[0],
                "TestC" : result_C,
                "TestP" : result_P,
            })
        i+=1
    print(json.dumps(failed_test,indent=4))
    Output(failed_test,32)

def Test_x64():
    i = 0
    failed_test = []
    while i < 10 :
        if i % 2 == 0:
            ans = TestDouble(random.randint(-9223372036854775808,9223372036854775807))
            pass
        else:
            ans = TestDouble(random.uniform(-9223372036854775808,9223372036854775807)/1000)
            pass
        result_C = []
        result_P = []
        threads = []
        threads.append(Thread(target=lunch,args=('testC',ans[1],result_C,4)))
        threads.append(Thread(target=lunch,args=('testP',ans[1],result_P,4)))
        # lunch('testC',ans[1],result_C,1)
        # lunch('testP',ans[1],result_P,1)
        # print(json.dumps(result_C,indent=4))
        for thread in threads:
            thread.start()

        for thread in threads:
            thread.join()
            
        if float(result_C[0]["float"]) == float(result_P[0]['float']) and int(result_C[0]['integer']) == int(result_P[0]['integer']):
            pass
        else:
            failed_test.append({
                "test bitpattern" : ans[1],
                "Ans Float":ans[0],
                "TestC" : result_C,
                "TestP" : result_P,
            })
        i+=1
    # print(json.dumps(failed_test,indent=4))
    Output(failed_test,64)

def Output(failed_test,bits):
    with open('test_x{}.json'.format(bits),'w') as f:
        f.write(json.dumps(failed_test,indent=4))

def main():
    system('gcc -o testC hw3.c')
    system('gcc -o testP test.c')
    processes = []
    processes.append(Process(target=Test_x32,))
    processes.append(Process(target=Test_x64,))
    for process in processes:
        process.start()
    for process in processes:
        process.join()

if __name__ == '__main__':
    main()
