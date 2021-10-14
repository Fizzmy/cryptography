def fast_pow(a,m,p):
    ans=1;
    while m:
        if m&1:
            ans=ans*a%p
        m>>=1
        a=a*a%p
    return ans
def output(x,dep,f):
    if dep==0:
        return
    output(x>>8,dep-1,f)
    if (x&255):
        f.write(chr(x&255))
if __name__=="__main__":
    s=""
    n=0
    d=0
    with open("public.txt","r") as f:
        s=f.read()
        t=s.split('\n')
        n=int(t[0])
    with open("secret.txt","r") as f:
        s=f.read()
        t=s.split('\n')
        d=int(t[2])
    with open("rsa_encode.txt","r") as f:
        s=f.read()
        t=s.split('\n')[:-1]
        with open("rsa_decode.txt","w") as f2:
            for x in t:
                e=fast_pow(int(x),d,n)
                output(e,16,f2)
    
   
    num=len(s)
