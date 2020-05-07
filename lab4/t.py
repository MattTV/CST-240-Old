import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-h', action="store_false", default=True)

args = parser.parse_args()

print(args.o)
