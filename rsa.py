def fast_pow(a,m,p):
    ans=1;
    while m:
        if m&1:
            ans=ans*a%p
        m>>=1
        a=a*a%p
    return ans
if __name__=="__main__":
    s=""
    n=0
    e=0
    with open("public.txt","r") as f:
        s=f.read()
        t=s.split('\n')
        n=int(t[0])
        e=int(t[1])
    with open("passage.txt","r") as f:
        s=f.read()
    
   
    num=len(s)
    with open("rsa_encode.txt","w") as f:
        for i in range(0,num,16):
            key=0
            for j in range(16):
                if (i+j<num):
                    key=(key<<8)+ord(s[i+j])
                else:
                    key=(key<<8)
            f.write(str(fast_pow(key,e,n)))
            f.write("\n")