#! /usr/bin/bash

import sys
from rsa import *

def printHelp():
    print("Usage: \nmain.py -g")
    print("main.py -e inputFile -o ouputFile -k publicKey")
    print("main.py -d inputFile -o ouputFile ")
    print("Options")
    print("-g,--generate : To generate public key and private key")
    print("-e,--encrypt :  Encrypt")
    print("-i,--input :  Input file")
    print("-k,--key :   public key file")

def generateKeys():
    ## Generating Keys
    e,d,n = generate(getPrime(),getPrime(),key_size = 128)
    export(e,d,n)
    print("Keys Generated")

def get_e_n(public_key):
    with open(public_key,'r') as fp:
        _,e,n = fp.readline(),int(fp.readline()),int(fp.readline())
    return e,n

def Encrypt(public_key,text_file):
    text = ""
    e = 0
    n = 0

    ## Reading public key
    with open(public_key,'r') as fp:
        _,e,n = fp.readline(),int(fp.readline()),int(fp.readline())

    with open(text_file,'r') as fp:
        text = fp.read()
    cipher_text = encrypt(text,e,n)

    with open("encrypted.txt",'w') as fp:
        for i in cipher_text:
            fp.write(f"{i}\n")
    print("File Encrypted")

def Decrypt(text_file):
    e = 0
    n = 0
    cipher_text = []

    ## Reading private Key
    with open('private.key','r') as fp:
        _,d,n = fp.readline(),int(fp.readline()),int(fp.readline())


    with open(text_file,'r') as fp:
        cipher_text = [ int(i) for i in fp.readlines()]

    original_message = decrypt(cipher_text,d,n)
    with open("decrypted.txt",'w') as fp:
        for ch in original_message:
            fp.write(f"{ch}")

    print("File Decrypted")

if __name__ == '__main__':
    if len(sys.argv) <= 1:
        printHelp()
    else:
        public_key = ""
        text_file = ""
        keyFile = ""
        outputFile = ""
        gen = False
        enc = False
        dec = False
        i = 1
        while i != len(sys.argv):
            if sys.argv[i] == '-g' or sys.argv[i] == '--generate':
                gen = True
                i += 1
            elif sys.argv[i] == '-e' or sys.argv[i] == '--encrypt':
                enc = True
                i += 1
            elif sys.argv[i] == '-d' or sys.argv[i] == '--decrypt':
                dec = True
                i += 1
            elif sys.argv[i] == '-i' or sys.argv[i] == '--input':
                i += 1
                text_file = sys.argv[i]
            elif sys.argv[i] == '-o' or sys.argv[i] == '--output':
                i += 1
                outputFile = sys.argv[i]
            elif sys.argv[i] == '-k' or sys.argv[i] == '--key' :
                i += 1
                public_key = sys.argv[i]
            else:
                i += 1

        if gen == True:
            generateKeys()
            exit(0)
        elif enc == True:
            if public_key == "" or text_file == "" :
                printHelp()
            else:
                Encrypt(public_key,text_file)
        elif dec == True:
            if  text_file == "":
                printHelp()
            else:
                Decrypt(text_file)
        else:
            printHelp()





