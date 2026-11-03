# calcc
*NOTE: Some stuff are broken, this is not finished because it's a beta release*

calcc - a calculator compiler that translates math into assembly

Right now, there are some stuff that are broken, division is broken, and also it can't subtract into negative numbers.

## How to use it
First, create a `.txt` file
```shell
cat <<< 'EOF' > math.txt
5 + 8
EOF
```

now compile it `./calcc math.txt` you should get a `math.asm` file

inside of that math.asm file is the NASM x86_64 assembly instructions for 5 + 8

## Building
run `make` to build and run `make install` with root to install

it will install it to `/usr/bin` so if you want to install it to `/usr/local/bin` you may need to modify the makefile.

## Known Issues
- Division is not working
- You can't subtract into negative numbers
- And some stuff hasn't been tested yet
