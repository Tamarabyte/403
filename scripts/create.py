#!/usr/bin/env python

import sys

def help():
    print("uvainit [number] [name]", file=sys.stderr)

def touch(path):
    with open(path, 'a'):
        os.utime(path, None)
        
def makeFile(dir, file):
    with open(path, 'w') as f:
        print("--> {}:\n".format(file))
        input_str = sys.stdin.read()
        f.write(input_str)
        
def makeTemplate(number, name, dir, filename):
    topics = {
        "Data Structures" : ".DataStructures.tag", 
        "Strings" : ".Strings.tag", 
        "Sorting" : ".Sorting.tag", 
        "Arithmetic" : ".Arithmetic.tag",
        "Combinatorics" : ".Combinatorics.tag", 
        "Number Thoery" : ".NumberTheory.tag", 
        "Backtracking" : ".Backtracking.tag", 
        "Graph Traversal" : ".GraphTraversal.tag", 
        "Graph Algorithms" : ".GraphAlgorithms.tag", 
        "Dynamic Programming" : ".DynamicProgramming.tag", 
        "Geometry" : ".Geometry.tag", 
        "Other" : ".Other.tag"
        }
    
    difficulties = {
        "trivial" :  ".trivial.tag",
        "non-trivial" : ".non-tri.tag" 
    }
    
    while topic not in topics.keys():
        topic = input("Topic: ")
    
    touch(dir + "/" + topics[topic])
        
    while difficulty not in ["trivial", "non-trivial"]:
        difficulty = input("Difficulty (trivial/non-trivial): ")
    
    touch(dir + "/" + difficulties[difficulty])
    
    template = """/* UVa problem: {} - {}
 *
 * Topic: {}
 *
 * Level: trivial/non-trivial: {}
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
 */
 
#include <cstdio>
using namespace std;

int main() {
    
}""".format(number, name, topic, difficulty)
 
    with open(dir + filename, 'w') as f:
        f.write(itemplate)

def initiate(number):
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
    
    if os.stat(number + "_" + name)
    mkdir
    
def main():
    if (len(sys.argv) != 3):
        help()
        sys.exit(1)
    
    initiate(sys.argv[1])

			
if __name__ == "__main__":
	main()