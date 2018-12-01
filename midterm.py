

def main():
    a = 0
    with open('score.txt',"r") as f:
        data = f.readlines()
        
        for i in data:
            i.rstrip('\n')
            if int(i) > 67:
                a += 1
        print(1 - a/len(data))
        print(a)

if __name__=='__main__':
    main()