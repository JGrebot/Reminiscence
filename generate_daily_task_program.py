#!/usr/env/python3
# 
help_str = """
By Jérémy Grebot, 09/04/2023.
This script generate a daily task program yaml file. This file has the format:
    Day1:
        - 1
        - 2
    Day2:
        - 1
    Day3:
        - 1
        - 2
        - 3
    etc..
This yaml files is used by the Reminiscence program (see
https://github.com/JGrebot/Reminiscence). Each category (either 1, or 2, or 3
or ...) frequency is controlled by the --CatFreq optional argument.
 
Usage:
    python3 generate_daily_task_program.py --help
    python3 generate_daily_task_program.py 90 7
    python3 generate_daily_task_program.py 90 7 --CatFreq 1 2 5 7 11 17 23

Dependencies:
   argparse, sys

"""
import argparse
import sys
from argparse import RawTextHelpFormatter
from argparse import ArgumentParser

#
# Parameters parsing
#
parser = ArgumentParser(description=help_str, formatter_class=RawTextHelpFormatter)
# parser = argparse.ArgumentParser(description=help_str)
parser.add_argument('nbDay', 
                    default=90, 
                    metavar='nbDay', 
                    type=int, 
                    help='The total number of day')
parser.add_argument('nbCat', 
                    default=7, 
                    metavar='nbCat', 
                    type=int, 
                    help='The total number of category')
parser.add_argument('--CatFreq', 
                    default=[1, 2, 5, 7, 11, 17, 23, 29], 
                    metavar='CatFrequency', 
                    type=int, 
                    nargs='+',
                    help='The frequency for each category')
args = parser.parse_args()

nb_day = args.nbDay
nb_cat = args.nbCat
cats_frequency = args.CatFreq


#
# Checking enough category frequency are provided (8 by default).
#
if len(cats_frequency) < nb_cat:
    print("Please provide as many category frequency (" +   \
          str(len(cats_frequency)) +                        \
          " provided) as you specified category (" +        \
          str(nb_cat) + ").")
    print("Error !")
    sys.exit()


#
# Program
#
all_days = range(1, nb_day+1)
all_cats = range(0, nb_cat)

histogram_cats = {}
for c in all_cats:
    histogram_cats[str(c)] = 0

for d in all_days:
    to_print = "Day" + str(d) + ": \n"
    for c in all_cats:
        if(d%cats_frequency[c] == 0):
            to_print += "    - " + str(c+1) + "\n"
            histogram_cats[str(c)] += 1
    print(to_print[0:-1])


#
# Print histogram_cats if required (might be useful)
#
display_histogram = False
if(display_histogram):
    print("histogram_cats = {")
    for key in histogram_cats.keys():
        print("     " + key + ": " + str(histogram_cats[key]) + ",")
    print("}")

