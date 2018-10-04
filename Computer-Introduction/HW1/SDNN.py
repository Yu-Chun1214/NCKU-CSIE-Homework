import numpy
import matplotlib.pyplot as plt
import re

def main():
    """
    main function
    """
    with open('./peakposition.txt','r') as f:
        text_list = f.readlines()
        data = dataProcess(text_list)
        interval = Interval(data)
        interval *= 2
        ans = numpy.std(interval)
        f = numpy.fft.fft(interval)
        plt.plot(f)
        plt.show()
        print(ans)

def dataProcess(text_list:list):
    """
    convert the text_list readed from peakposition.txt to integer

    parameter :
    type is str list

    return the integer list data
    """
    data = [int(i) for i in text_list]
    return data

def Interval(data:list):
    length = len(data)
    interval = []
    interval.append(2*data[0])
    for i in range(1,length):
        interval.append(2*(data[i] - data[i-1]))
    return interval

if __name__ == '__main__':
    main()
