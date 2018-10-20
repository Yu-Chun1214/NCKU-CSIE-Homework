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


# Test binary to Decimal
# Test Part 1 and Part 2
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

def test(arg1,arg2):
    result = subprocess.check_output('./a.out {} {}'.format(arg1,arg2),shell=True)
    print(result.decode('utf-8').rstrip('\n'))

def TestMode2(num:int(),pattern:str(),fail_test):
    
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

def TestMode2_2(num:int,pattern:str(),failed_test):
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

def TestMode3(num:int(),pattern:str(),fail_test):
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

def test_x32():
    i = 0
    failed_test = []
    threads=[]
    while i < 5 :
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
        threads.append(threading.Thread(target=TestMode2,args=(test_int,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestMode3,args=(test_float,ans[1],failed_test)))
        threads.append(threading.Thread(target=TestMode2_2,args=(test_float,ans[1],failed_test)))
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()
        threads = []
        i += 1
    return failed_test

if __name__ == '__main__':
    result = test_x32()
    if len(result) == 0:
        print("All successful")
    else:
        print(json.dumps(result,indent=4))
