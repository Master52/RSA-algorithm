# RSA-algorithm

Python implementation of RSA algorithm.

![](https://github.com/Master52/RSA-algorithm/blob/master/output.gif)

## Usage
Generating Keys:
```code
    python main.py -g
```
Generates two file `private.key` and `public.key`

Encrypting file:
```code
    python main.py -e -i <input file> -k <public key>
```

Decypting file:
```code
    python main.py -r -i <input file>
```
_Note: while decrypting file `private.key` should be in the directory where the file has been run_

For further explanation visit [BloggerDrive](https://www.bloggerdrive.com/understanding-and-implementing-rsa-algorithm-in-python/)

