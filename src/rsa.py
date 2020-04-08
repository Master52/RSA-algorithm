import random
import math

__DEBUG__ = True
PRIME_LIMIT = 1000000000000

class RSA(object):

    def __init__(self,public_key = 0,private_key = 0,n = 0,phi = 0):
        self.__public_key = public_key
        self.__private_key = private_key
        self.__n = n
        self.__phi = phi

    def generate(self,p_num1,p_num2,key_size = 32):
        self.__n = p_num1 * p_num2
        self.__phi = (p_num1 - 1) * (p_num2 - 1)
        self.__public_key = self.generatePublicKey(key_size)
        self.__private_key = self.generatePrivateKey()

        if __DEBUG__:
            print(f"""n = {self.__n}\nphi = {self.__phi}\npublicKey = {self.__public_key}\nprivateKey = {self.__private_key}""")
        self.export()

    def export(self):
        with open("public.key","w") as fp:
            fp.write(f"RSA PUBLIC KEY:\n{self.__public_key}\nEND")
            print("Public Key Written")
        with open("private.key","w") as fp:
            fp.write(f"RSA PRIVATE KEY:\n{self.__private_key}\n{self.__n}\nEND")
            print("Private Key written")


    def generatePublicKey(self,key_size):
        e = random.randint(2**(key_size-1),2**key_size - 1)
        g = gcd(e,self.__phi)
        while g != 1:
            e = random.randint(2**(key_size-1),2**key_size - 1)
            g = gcd(e,self.__phi)

        return e

    def generatePrivateKey(self):
        d =  egcd(self.__public_key,self.__phi)[1]
        d = d % self.__phi
        if d < 0 :
            d += self.__phi
        return d

    def encrypt(self,text):
        ctext = [pow(ord(char),self.__public_key,self.__n) for char in text]
        return ctext

    def decrypt(self,ctext):
        try:
            text = [chr(pow(char,self.__private_key,self.__n)) for char in ctext]
            return "".join(text)
        except TypeError as e:
            print(e)


def egcd(a,b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)

    return (g, x - (b // a) * y, y)


def gcd(e,phi):
    temp = 0
    while True:
        temp = e % phi
        if temp == 0:
            return phi
        e = phi
        phi = temp


def isPrime(num):
    if num < 2 : return False
    if num == 2 : return True
    if num & 0x01 == 0 : return False
    n = int(math.sqrt(num))
    for i in range(3,n,2):
        if num % i == 0:
            return False

    return True

def getPrime(limit = 2048):
    num = 0
    while True:
        num = random.randint(0,limit)
        if isPrime(num):
            break
    return num

if __name__ == '__main__':
    rsa = RSA()
    rsa.generate(getPrime(PRIME_LIMIT),getPrime(PRIME_LIMIT),key_size = 128)
    plainText = "This is plain Text"
    cipher = rsa.encrypt(plainText)
    dicipher = rsa.decrypt(cipher)

