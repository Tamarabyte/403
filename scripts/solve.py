#!/usr/bin/env python

import sys
import os
import re
import shutil

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
    "Trivial" :  ".trivial.tag",
    "Non-Trivial" : ".non-tri.tag" 
}

def checkTag(tagDict):
    
    string = "";
    
    count = 0;
    for name, tag in tagDict.items():
        if os.path.exists(os.getcwd() + "/" + tag):
            count += 1;
            string = name
    
    if count > 1:
        printf("Too many tags for difficulty or topic.", file=sys.stderr)
        sys.exit()
    
    if count == 0:
        printf("Missing difficulty or topic tag.", file=sys.stderr)
        sys.exit()
        
    return string;

def processSolve(num, name):
    topic = checkTag(topics)
    diff = checkTag(difficulties)
    
    mandatory = ""
    if os.path.exists(os.getcwd() + "/" + ".mandatory.tag"):
        mandatory = " [Mandatory]"
    
    percent = ""
    with open(os.getcwd() + "/" + ".percent.tag") as f:
        percent = f.read()
        percent = percent.strip()
        
    with open(os.getcwd() + "/../solutions/readme.txt", "r") as f:
        readme = f.read()
        
    with open(os.getcwd() + "/../solutions/readme.txt", "w") as f:
        if name in readme:
            print("Already solved", file=sys.stderr)
            f.write(readme)
            sys.exit()
        
        if diff == "Trivial":
            digit = int(re.search("\nTrivial: (\d+)", readme).group(1))
            digit += 1
            readme = re.sub("\nTrivial: \d+", "\nTrivial: %d"% digit, readme)

        elif diff == "Non-Trivial":
            digit = int(re.search("Non-Trivial: (\d+)", readme).group(1))
            digit += 1
            readme = re.sub("Non-Trivial: \d+", "Non-Trivial: %d"% digit, readme)
    
        digit = int(re.search("Total: (\d+)", readme).group(1))
        digit += 1
        readme = re.sub("Total: \d+", "Total: %d"% digit, readme)
        
        line = "{num} - {name} - {diff}{mandatory}".format(**locals())
        if diff == "Non-Trivial":
            line += " ({percent}%)".format(**locals())
        line += "\n"
        
        digit = re.search(topic + ": (\d+)\n--------------------\n", readme)
        if digit is None:
            readme += "\n\n" + topic + ": 1\n--------------------\n"
            readme += line;
        else:
            digit = int(digit.group(1)) + 1;
            readme = re.sub(topic + ": \d+\n--------------------\n", topic + ": %d\n--------------------\n%s"%(digit, line), readme)
    
        f.write(readme)
    
    shutil.copy2(os.getcwd() + "/UVa" + num + ".cpp", os.getcwd() + "/../solutions/" + "/UVa" + num + ".cpp")
    
        
    with open(os.getcwd() + "/" + ".solved.tag", 'w') as f:
        f.write("")
    
    print(readme)

def help():
    print("Must be in UVA directory with format NUM_NAME", file=sys.stderr)
    
def main():
    try:
        dir = os.path.split(os.getcwd())[1]
        num, name = dir.split('_')
    except:
        help()
        sys.exit()
    
    if not num.isdigit():
        help()
        sys.exit()
    
    processSolve(num, name)
    
if __name__ ==  "__main__":
    main()