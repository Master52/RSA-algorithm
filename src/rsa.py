import random

PRIME_LIMIT = 1000000000000
__DEBUG__ = False

def generate(p_num1,p_num2,key_size = 128):
    n = p_num1 * p_num2
    tot = (p_num1 - 1) * (p_num2 - 1)
    e = generatePublicKey(tot,key_size)
    d = generatePrivateKey(e,tot)

    if __DEBUG__ == True:
        print(f"n =    {n}" )
        print(f"tot = {tot}")
        print(f"e =    {e}" )
        print(f"d =    {d}" )

    return e,d,n

def export(e,d,n):
    ## Saving keys to file
    with open("public.key","w") as fp:
        fp.write(f"RSA PUBLIC KEY:\n{e}\n{n}\nEND")
        print("Public Key Written")
    with open("private.key","w") as fp:
        fp.write(f"RSA PRIVATE KEY:\n{d}\n{n}\nEND")
        print("Private Key written")


def generatePublicKey(tot,key_size):
    e = random.randint(2**(key_size-1),2**key_size - 1)
    g = gcd(e,tot)
    while g != 1:
        e = random.randint(2**(key_size-1),2**key_size - 1)
        g = gcd(e,tot)

    return e

def generatePrivateKey(e,tot):
    d =  egcd(e,tot)[1]
    d = d % tot
    if d < 0 :
        d += tot
    return d

def encrypt(text,e,n):
    ctext = [pow(ord(char),e,n) for char in text]
    return ctext

def decrypt(ctext,d,n):
    try:
        text = [chr(pow(char,d,n)) for char in ctext]
        return "".join(text)
    except TypeError as e:
        print(e)


def egcd(a,b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)

    return (g, x - (b // a) * y, y)


def gcd(e,tot):
    temp = 0
    while True:
        temp = e % tot
        if temp == 0:
            return tot
        e = tot
        tot = temp


def isPrime(num):
    if num < 2 : return False
    if num == 2 : return True
    if num & 0x01 == 0 : return False
    n = int(num ** 0.5 )
    for i in range(3,n,2):
        if num % i == 0:
            return False

    return True

def getPrime(limit = PRIME_LIMIT):
    num = 0
    while True:
        num = random.randint(0,limit)
        if isPrime(num):
            break
    if __DEBUG__ == True:
        print(f"Generated Prime number: {num}")
    return num

if __name__ == '__main__':
    e,d,n = generate(getPrime(),getPrime(),key_size = 128)
    export(e,d,n)
    plainText = "This is plain Text"
    print(f"\nOriginal Text: {plainText}")
    cipher = encrypt(plainText,e,n)
    print(f"\ncipher Text: {cipher}")
    dicipher = decrypt(cipher,d,n)
    print(f"\ndecryped Text: {dicipher}")

