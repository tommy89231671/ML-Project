# -*- coding: utf-8 -*-
"""
Created on Sat Jan 13 15:33:11 2018

@author: tommy
"""
x=open("data.txt",'r')
line=x.readline()
counter=0
for line in x.readlines():
    if line.find("Iteration")!=-1:
        t=line.find(":")
        #print(line.find("is")+3,line.find("\n"))
        
        print(line[line.find("is")+3:line.find("\n")])
    elif line.find("perplexity"):
        print(line)
    counter+=1
    if counter==150:
        break
        