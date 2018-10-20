"""
因為作業2有bug自己沒發現
氣一個怒寫測試程式
希望能幫我找bug

這份測試程式會吃掉你很多網路流量
請謹慎使用

寫完test_x32還是覺得自己好弱
跟Queensland University的測資 根本天差地遠嗚嗚

"""


__author__ = 'Yu-Chun,Lin'

import json
import threading
import multiprocessing
import requests
import bs4
import subprocess
import random
import os
from requests_html import HTMLSession

Decimal_To_Binary_x32 = 'https://www.binaryhexconverter.com/hesapla.php?fonksiyon=bin2dec&deger={}&pad=false&v=2'

# Test binary to float and float to Decimal 
Decimal_To_float_x32 = 'https://www.h-schmidt.net/FloatConverter/binary-json.py?decimal={}'
Binary_To_float_x32 = 'https://www.h-schmidt.net/FloatConverter/binary-json.py?binary={}'


Decimal_To_double_x64 = 'https://www.exploringbinary.com/floating-point-converter'

session = HTMLSession()
lock = threading.Lock()

def TestFloat(*,num=None,pattern:str=None,NumToString=True,ansDecimal=None,ansBinary=None)->list:
    # print(num)
    if num is None and pattern is None:
        raise TypeError('Test Float need to input num or bitpattern')
    elif num is not None:
        response = session.get(Decimal_To_float_x32.format(num))
    elif pattern is not None:
        response = session.get(Binary_To_float_x32.format(pattern))
    if response.status_code != 200:
        return None
    ans = json.loads(response.text)
    ansDecimal = ans["highprecision_decimal"]
    ansBinary = ans["binaryRepr"]
    if NumToString == False:
        return [float(ans["highprecision_decimal"]),ans["binaryRepr"]]
    elif NumToString == True:
        return [ans["highprecision_decimal"],ans["binaryRepr"]]

def BitpatternTest_x32(pattern:str)->list:
    response = session.get(Decimal_To_Binary_x32.format(pattern))
    if response.status_code != 200:
        return None
    ans = response.text
    return [int(ans),pattern]

def TestDouble(num)->list:
    form_data = {
        'd2f_input_decimal': str(num),
        'd2f_convert': 'Convert',
        'd2f_precision_53_chosen': '1',
        'd2f_input_decimal_format_chosen': '1',
        'd2f_input_rawBinary_format_chosen': '1',
    }
    input_response = requests.post(Decimal_To_double_x64,data=form_data)
    # print(input_response.status_code)
    soup = bs4.BeautifulSoup(input_response.text,'html.parser')
    target = soup.find_all('input','output_short_box')
    target = target[0].attrs['value'].replace(' ','')
    return [num, target]

def TestMode2(num,pattern:str(),fail_test):
    
    # print('Mode 2')
    test_result = subprocess.check_output('./a.out 2 {}'.format(num),shell=True)
    test_result = test_result.decode('utf-8').rstrip('\n')
    if test_result == pattern:
        print('Mode 2 successfully test')
        pass
    else:
        lock.acquire()
        print('Mode 2 failed test')
        fail_test.append({
            'mode': 2,
            'Test Number':num,
            'Test Bitpattern' : pattern,
            'Error Bitpattern' : test_result,
        })
        lock.release()

def TestMode2_2(num,pattern:str(),failed_test):
    test_result = subprocess.check_output('./a.out 2 {}'.format(num),shell=True)
    test_result = test_result.decode('utf-8').rstrip('\n')
    ans = TestFloat(pattern=test_result,NumToString=False)
    if ans[1] == test_result:
        print('Mode 2 back test successfully')
    else:
        lock.acquire()
        print('Mode 2 back test failed')
        failed_test.append({
            'mode' : 2,
            'Test Number' : num,
            'Error Bitpattern' : test_result,
            'Ans Bitpattern' : ans[1],
        })
        lock.release()

def TestMode3(num,pattern:str(),fail_test):
    # print('Mode 3')
    test_result = subprocess.check_output('./a.out 3 {}'.format(num),shell=True)
    test_result = test_result.decode('utf-8').rstrip('\n')
    if test_result == pattern:
        print('Mode 3 successfully test')
        pass
    else:
        print('Mode 3 failed test')
        fail_test.append({
            'mode': 3,
            'Test Number':num,
            'Test Bitpattern' : pattern,
            'Error Bitpattern' : test_result,
        })

def TestItself(Mode1num,mode1_4,mode,failed_test:list(),type:str):
    """
    ./a.out test itself

    parameter:
        Mode1num : 
            input a number which is generate in mode 1
        mode1_4:
            select mode 1 or mode 4
        mode:
            select mode 2 3 or mode 5 6
        failed_test:
            a list type variable which record the fail test information
        type:
            select int or float 
    """
    test_result = subprocess.check_output('./a.out {} {}'.format(mode,Mode1num),shell=True)
    test_result = test_result.decode('utf-8').rstrip('\n')
    result = subprocess.check_output('./a.out {} {}'.format(mode1_4,test_result),shell=True)
    result = result.decode('utf-8').rstrip('\n')
    result = json.loads(result)
    if type == 'integer':
        ans = int(result[type])
    else:
        ans = float(result[type])
    if Mode1num == ans:
        print("Mode {} test itself successfully".format(mode))
    else:
        lock.acquire()
        print('Mode {} test itself failed'.format(mode))
        failed_test.append({
            'mode' : mode,
            'Test Number' : Mode1num,
            'Error Bitpattern' : test_result,
            'Type' : type,

        })
        lock.release()

def TestMode(mode,num,pattern:str(),failed_test):
    test_result = subprocess.check_output('./a.out {} {}'.format(mode,num),shell=True)
    test_result = test_result.decode('utf-8').rstrip('\n')
    if test_result == pattern:
        print('Mode {} successfully test'.format(mode))
        pass
    else:
        lock.acquire()
        print('Mode {} failed test'.format(mode))
        failed_test.append({
            'mode': mode,
            'Test Number':num,
            'Test Bitpattern' : pattern,
            'Error Bitpattern' : test_result,
        })
        lock.release()

def test_x32():
    i = 0
    failed_test = []
    threads=[]
    while i < 10 :
        if i % 2 == 0:
            ans = TestFloat(num=random.randint(-2147483648,2147483647),NumToString=False)
            pass
        else:
            ans = TestFloat(num=round(random.uniform(-2147483648,2147483647),8),NumToString=False)
            pass
        result_dict = subprocess.check_output('./a.out {} {}'.format(1,ans[1]),shell=True)
        
        test_data = json.loads(result_dict.decode('utf-8').rstrip('\n'))
        test_int = int(test_data["integer"])
        test_float = float(test_data["float"])
        if test_float == ans[0]:
            pass
        else:
            failed_test.append({
                'mode' : 1,
                'Test Number' : ans[0],
                'Test Bitpattern' : ans[1],
                'Error Integer' : test_int,
                'Error Float' : test_float,
            })
            continue
        # Online test
        threads.append(threading.Thread(target=TestMode2,args=(test_int,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestMode3,args=(test_float,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestMode2_2,args=(test_float,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestItself,args=(test_int,1,2,failed_test,"integer")))
        threads.append(threading.Thread(target=TestItself,args=(test_float,1,3,failed_test,"float")))
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()
        threads = []
        i += 1
    print(json.dumps(failed_test,indent=4))
    return failed_test

def test_x64():
    i = 0
    failed_test = []
    threads = []
    test_datas = []
    while i < 10:
        
        if i % 2 == 0:
            ans = TestDouble(random.randint(-9223372036854775808,9223372036854775807))
            pass
        else:
            ans = TestDouble(random.uniform(-9223372036854775808,9223372036854775807))
            pass
        result_dict = subprocess.check_output('./a.out {} {}'.format(4,ans[1]),shell=True)
        test_data = json.loads(result_dict.decode('utf-8').rstrip('\n'))
        test_int = int(test_data["integer"])
        test_float = float(test_data["float"])
        i += 1
        if format(test_float,'.20g') == format(ans[0],'.20g'):
            print("successful")
            print(format(test_float,'.20g'),format(ans[0],'.20g'),sep='\n')
            test_datas.append([ans[1],ans[0]])
            pass
        else:
            failed_test.append({
                'mode' : 4,
                'Test Number' : ans[0],
                'Test Bitpattern' : ans[1],
                'Error Integer' : test_int,
                'Error Float' : test_float,
            })
            continue
        
        threads.append(threading.Thread(target=TestMode,args=(5,test_int,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestMode,args=(6,test_float,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestItself,args=(test_int,4,5,failed_test,"integer")))
        threads.append(threading.Thread(target=TestItself,args=(test_float,4,6,failed_test,"float")))
        for thread in threads:
            thread.start()

        for thread in threads:
            thread.join()
        threads = []
    print(json.dumps(failed_test,indent=4))
    with open('test_data_x64.txt','w') as f:
        for i in test_datas:
            f.write('{}    {}\n'.format(i[0],format(i[1],'.20g')))
        f.close()
    return failed_test
        
    # TestMode4(1,'2','3')


def main():
    failed_test_x32_list = list()
    failed_test_x64_list = list()
    processes = []
    processes.append(multiprocessing.Process(target=test_x32,))
    processes.append(multiprocessing.Process(target=test_x64))
    for process in processes:
        process.start()
    for process in processes:
        process.join()

    print(json.dumps(failed_test_x32_list,indent=4))
    print('-'*80)
    print(json.dumps(failed_test_x64_list,indent=4))

if __name__ == '__main__':
    os.system('gcc hw3.c')
    main()