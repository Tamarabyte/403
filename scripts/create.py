#!/usr/bin/env python

import sys
import os

def help():
    print("uvainit [number] [name]", file=sys.stderr)

def touch(path):
    with open(path, 'a'):
        os.utime(path, None)
        
def makeFile(dir, file):
    path = dir + "/" + file;
    with open(path, 'w') as f:
        print("--> {}:".format(file))
        input_str = sys.stdin.read()
        f.write(input_str)
        
def makeTemplate(number, name, dir, filename):
    topics = {
        "Data Structures" : ".DataStructures.tag", 
        "Strings" : ".Strings.tag", 
        "Sorting" : ".Sorting.tag", 
        "Arithmetic" : ".Arithmetic.tag",
        "Combinatorics" : ".Combinatorics.tag", 
        "Number Theory" : ".NumberTheory.tag", 
        "Backtracking" : ".Backtracking.tag", 
        "Graph Traversal" : ".GraphTraversal.tag", 
        "Graph Algorithms" : ".GraphAlgorithms.tag", 
        "Dynamic Programming" : ".DynamicProgramming.tag", 
        "Geometry" : ".Geometry.tag", 
        "Other" : ".Other.tag"
        }
    
    difficulties = {
        "T" :  ".trivial.tag",
        "N" : ".non-tri.tag" 
    }
    
    topic = None
    while topic not in topics.keys():
        topic = input("Topic: ")
    touch(dir + "/" + topics[topic])
    
    difficulty  = None
    while difficulty not in ["T", "N"]:
        difficulty = input("Difficulty (T/N): ")
    touch(dir + "/" + difficulties[difficulty])
    
    percentage  = None
    while percentage is None:
        percentage = input("Percent Solved: ")
    
    touch(dir + "/" + ".percent.tag")
    with open(dir + "/" + ".percent.tag", "w") as f:
        f.write(percentage + "\n")
    
    mandatory = None
    while mandatory not in ["Y", "N"]:
        mandatory = input("Mandatory? (Y/N): ")
    
    if mandatory == "Y":
        touch(dir + "/" + ".mandatory.tag")
    
    template = """/* UVa problem: {number} - {name}
 *
 * Topic: {topic}
 *
 * Level: trivial/non-trivial: {difficulty}
 *
 * Brief problem description:
 *
 * Solution Summary:
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 * Language: C++11
 */
 
#include <cstdio>
using namespace std;

int main() {{
    
}}""".format(**locals())
 
    with open(dir + filename, 'w') as f:
        f.write(template)

def initiate(number, name):
    dir = os.getcwd() + "/" + str(number) + "_" + name
    
    # create the directory
    if not os.path.exists(dir):
        os.makedirs(dir)
    else:
        print("Directory already exists for problem #" + number + ".", file=sys.stderr)
        sys.exit(1)
    
    # create the files
    makeFile(dir, "input.txt")
    makeFile(dir, "expected.txt")
    makeTemplate(number, name, dir, "/UVa" + str(number) + ".cpp")
    
def main():
    if (len(sys.argv) != 3):
        help()
        sys.exit(1)
    
    if (not sys.argv[1].isdigit()):
        help()
        sys.exit()
        
    initiate(sys.argv[1], sys.argv[2])

			
if __name__ == "__main__":
	main()