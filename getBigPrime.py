from random import randint
def fast_pow(a,m,p):
    ans=1;
    while m:
        if m&1:
            ans=ans*a%p
        m>>=1
        a=a*a%p
    return ans

def Miller_Rabin(p):
    if p%2==0:
        return 0
    m,k=p-1,0
    while m%2==0:
        m,k=m>>1,k+1
    a=randint(2,p-1)
    x=fast_pow(a,m,p)
    if x==1 or x==p-1:
        return 1
    while k>1:
        x=x*x%p
        if x==1:
            return 0
        if x==p-1:
            return 1
        k-=1
    return 0
def check(x):
    for t in range(40):
        if Miller_Rabin(x)==0:
            return 0
    return 1
def getPrime(n):
    num=0
    for i in range(int(n)):
        num=num*2+randint(0,1)
    while (check(num)==0):
        num+=1
    return num
def gcd(a,b):
    if b==0:
        return a
    return gcd(b,a%b)
def exgcd(a, b):
    if (b==0):
        return 1,0,a
    x,y,gcd=exgcd(b,a%b)
    return y,x-a//b*y,gcd

if __name__=='__main__':
    # 产生p,q
    print("请输入要生成的素数位数：")
    N=input()
    p,q=getPrime(N),getPrime(N)
    n=p*q
    # 选择e
    phi=(p-1)*(q-1)
    e=randint(3,phi-1)
    while (gcd(e,phi)!=1):
        e=randint(3,phi-1)
    d=exgcd(phi,e)[1]%phi
    with open("public.txt","w") as f1:
        f1.write(str(n)+"\n"+str(e))
    with open("secret.txt","w") as f2:
        f2.write(str(p)+"\n"+str(q)+"\n"+str(d))
    print("公钥:")
    print("n =",n)
    print("e =",e)
    print("私钥:")
    print("p =",p)
    print("q =",q)
    print("d =",d)