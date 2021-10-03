import socket
def main():
    port=11111
    c=socket.socket()
    print("socket created successfully")
    c.connect(('',port))
    s=s1=input("Enter data:")
    parity=input("Enter parity type:")
    l=[];d=[]
    p=0
    while 1:
        if 2**p>=p+len(s)+1:
            break
        p+=1
    #print(len(s),p)
    for i in range(p):
        l.append(2**i)
    #print(l)
    for i in range(1,len(s)+p+1):
        if i in l:
            d.insert(0,"x")
        else:
            d.insert(0,s1[-1])
            s1=s1[:-1]
    d=d[::-1]
    #print(len(s)+p)
    if parity=="even":
        for i in range(p):
            c1=0;j=l[i]
            while j<=len(s)+p:
                for _ in range(l[i]):
                    if j<=len(s)+p:
                        if d[j-1]=="1":
                            c1+=1
                    #print(j)
                        j+=1
                    #print(j)
                    else:
                        break
                j+=l[i]
                #print(i,j)
            #print(c)
            if c1%2==0:
                d[l[i]-1]="0"
            else:
                d[l[i]-1]="1"
            #print(l[i],d)
    elif parity=="odd":
        for i in range(p):
            c1=0;j=l[i]
            while j<=len(s)+p:
                for _ in range(l[i]):
                    if j<=len(s)+p:
                        if d[j-1]=="1":
                            c1+=1
                    #print(j)
                        j+=1
                    #print(j)
                    else:
                        break
                j+=l[i]
            if c1%2==0:
                d[l[i]-1]="1"
            else:
                d[l[i]-1]="0"
    #d[0]="0";
    c.sendall(str.encode("\n".join(["".join(d[::-1]),parity])))
    print(c.recv(1024).decode())
    c.close()
    
if __name__=="__main__":
    main()
