# Matt Volpe
# CST 240 - Linux Programming
# May 6, 2020

import argparse
from os import system
from sys import exit

def show_help():
    print("""
    Welcome to footest!
    This script tests the C program foo, ensuring that it exits successfully by returning 0.
    This script can test the program on a range of values, from a given start, to a specified end, and give feedback on the results.
    
    footest.py can take four possible arguments: -h, -e, -s, and -v.
    -h Brings up the help menu, where you are now.
    -e Specifies the end value to test foo with. If not specified, it will equal -s.
    -s Specifies the start value to test foo with. If not specified, it will equal -e.
    -v Will show extra details when functions fail.

    NOTE: If neither -e nor -s are specified, you will see this help menu again!""")

    exit()


parser = argparse.ArgumentParser(add_help=False)
    
parser.add_argument("-h", action="store_true", default=False)
parser.add_argument("-e", default=-1)
parser.add_argument("-s", default=-1)
parser.add_argument("-v", action="store_true", default=False) 

args = parser.parse_args()

if args.h:
    show_help()

end = int(args.e)
start = int(args.s)
verbose = args.v 
result = -1 

if start == -1 and end == -1:
    show_help()
elif end == -1:
    end = start
elif start == -1:
    start = end

if start > end:
    end = start

tempend = end + 1

for ii in range(start,tempend):
    result = int(system(f"./foo {ii}") / 256)

    if result == 0:
        print(f"{ii} was successful!")

    elif result == 1 and verbose == True:
        print(f"{ii} didn't work. It returned {result}. This means a command line argument was not supplied.")

    elif result == 2 and verbose == True:
        print(f"{ii} didn't work. It returned {result}. This means an invalid command line argument was supplied.")

    elif result == 3 and verbose == True:
        print(f"{ii} didn't work. It returned {result}. This means the program failed for another reason.")

    elif verbose == False:
        print(f"{ii} didn't work.")
