"""
因為作業2有bug自己沒發現
氣一個怒寫測試程式
希望能幫我找bug

這份測試程式會吃掉你很多網路流量
請謹慎使用

"""


__author__ = 'Yu-Chun,Lin'

import json
import threading
import requests
import bs4
from requests_html import HTMLSession


# Test binary to Decimal
# Test Part 1 and Part 2
Binary_To_Decimal_x32 = 'https://www.binaryhexconverter.com/hesapla.php?fonksiyon=bin2dec&deger={}&pad=false&v=2'

# Test binary to float and float to Decimal 
Decimal_To_float_x32 = 'https://www.h-schmidt.net/FloatConverter/binary-json.py?decimal={}'

Decimal_To_double_x64 = 'https://www.exploringbinary.com/floating-point-converter'

session = HTMLSession()

def TestFloat(num:int)->list:
    response = session.get(Decimal_To_float_x32.format(120))
    if response.status_code != 200:
        return None
    ans = json.loads(response.text)
    return [int(ans["highprecision_decimal"]),ans["binaryRepr"]]

def BitpatternTest_x32(pattern:str)->list:
    response = session.get(Binary_To_Decimal_x32.format(pattern))
    if response.status_code != 200:
        return None
    ans = response.text
    return [int(ans),pattern]

# def encoding(num):
#     code = ''
#     num = str(num)
#     for i in num:
#         if i == '-':
#             code += '045'
#         elif i == '.':
#             code += '046' 
#         elif int(i) in range(0,10):
#             code += '0'+str(int(i)+48)        
#     return code

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

