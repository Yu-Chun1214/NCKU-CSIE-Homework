"""
因為作業2有bug自己沒發現
氣一個怒寫測試程式
希望能幫我找bug

這份測試程式會吃掉你很多網路流量
請謹慎使用
.0  

"""


__author__ = 'Yu-Chun,Lin'

import json
import threading
import requests
import bs4
import subprocess
from requests_html import HTMLSession


# Test binary to Decimal
# Test Part 1 and Part 2
Decimal_To_Binary_x32 = 'https://www.binaryhexconverter.com/hesapla.php?fonksiyon=bin2dec&deger={}&pad=false&v=2'

# Test binary to float and float to Decimal 
Decimal_To_float_x32 = 'https://www.h-schmidt.net/FloatConverter/binary-json.py?decimal={}'
Binary_To_float_x32 = 'https://www.h-schmidt.net/FloatConverter/binary-json.py?binary={}'


Decimal_To_double_x64 = 'https://www.exploringbinary.com/floating-point-converter'

session = HTMLSession()

def TestFloat(*,num:int=None,pattern:str=None,NumToString=False)->list:
    if num is None and pattern is None:
        raise TypeError('Test Float need to input num or bitpattern')
    elif num is not None:
        # print(num,pattern)
        response = session.get(Decimal_To_float_x32.format(num))
    elif pattern is not None:
        response = session.get(Binary_To_float_x32.format(pattern))
    if response.status_code != 200:
        return None
    ans = json.loads(response.text)
    print(json.dumps(ans,indent=4))
    if NumToString == False:
        return [float(ans["highprecision_decimal"]),ans["binaryRepr"]]
    else:
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
# test('1','00000000000000000000000001100100')

# print(BitpatternTest_x32('00000000000000000000000001100100'))

print(TestFloat(pattern='11100000000000000000000000000000',NumToString=True))
# print('{:032b}'.format(-1))