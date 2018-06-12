# -*- coding: utf-8 -*-
"""
Created on Fri Dec 29 22:33:10 2017

@author: tommy
"""


import matplotlib.pyplot as plt
from numpy.linalg import eig
import numpy as np

from svmutil import *

y, x = svm_read_problem("train.txt")
yy,xx=svm_read_problem("test.txt")
#tmp="-c "+str(45)+" -g "+str(1/10)  
#print("C="+str(50)+"   gamma="+str(1/700))
#m = svm_train(y,x,tmp)
#p_label, p_acc, p_val = svm_predict(yy,xx, m)
for i in range(200,1001,200):
    for j in range(5,80,10):
        tmp="-c "+str(i)+" -g "+str(1/j)  
        print("C="+str(i)+"   gamma="+str(1/j))
        m = svm_train(y,x,tmp)
        p_label, p_acc, p_val = svm_predict(yy,xx, m)
        
