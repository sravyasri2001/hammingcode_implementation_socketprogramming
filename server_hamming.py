import socket
port=11111
soc=socket.socket()
print("socket created successfully")
soc.bind(('',port))
print("socket successfully binded")
soc.listen(5)
print("server listening...")
c,addr=soc.accept()
print("Connected with",addr)
s,parity=c.recv(2048).decode('utf-8').split('\n')
print("Data received from client:",s)
print("Parity type received from client:",parity)
s1="";l=[];d=[];p=0
while 1:
    if 2**p>=len(s)+1:
        break
    p+=1
for i in range(p):
    l.append(2**i)
d=list(s[::-1])#11001010011
if parity=="even":
    for i in range(p):
        c1=0;j=l[i]
        while j<=len(s):
            for _ in range(l[i]):
                if j<=len(s):
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
            s1+="0"
        else:
            s1+="1"
            #print(l[i],d)
elif parity=="odd":
    for i in range(p):
        c1=0;j=l[i]
        while j<=len(s)+p:
            for _ in range(l[i]):
                if j<=len(s):
                    if d[j-1]=="1":
                        c1+=1
                    #print(j)
                    j+=1
                    #print(j)
                else:
                    break
            j+=l[i]
        if c1%2==0:
            s1+="1"
        else:
            s1+="0"
error=int(s1[::-1],2)
if error==0:
    c.send(bytes("Data is not corrupted","utf-8"))
else:
    c.send(bytes("Data is corrupted","utf-8"))
    print("Error is present at bit:",error)
    if d[error-1]=="1":
        d[error-1]="0"
    else:
        d[error-1]="1"
print("Data originally sent by the client is:","".join(d[::-1])) 
soc.close()
    
