# -*- coding: utf-8 -*-
"""
Created on Fri Dec 29 16:55:52 2017

@author: tommy
"""
import matplotlib.pyplot as plt
from numpy.linalg import eig
import numpy as np

from svmutil import *

def read_file(X_name,T_name,mode,size):
    X=open(X_name,"r")
    T=open(T_name,"r")
    f=open(mode,"w")
    label=[]
    data=[]
    x_mean=np.zeros((784,1), dtype=np.float)
    for i in range(size):
        line=X.readline()
        tm=int(T.readline())
        label.append(tm)
        write_string=""
        write_string+=(str(tm)+' ')
        x=np.zeros((784,1), dtype=np.float)
        e=0
        for j in range(783):
            end=line.find(',',e)
            x[j]=float(line[e:end])
            x_mean[j]+=(x[j]/size)
            write_string+=(str(j)+":"+line[e:end]+" ")
            e=end+1
        end=line.find('\n')
        write_string+=("783:"+line[e:end]+"\n")
        x[783]=float(line[e:end])
        f.write(write_string)
        data.append(x)
    f.close()
    return label,data,x_mean    
def pca(train_data,x_mean):
    covariance=np.zeros((784,784), dtype=np.float) 

    for i in range(size):
        tmp=train_data[i]-x_mean
        covariance+=np.dot(tmp,tmp.transpose())
        
    for i in range(784):
        for j in range(784):
            covariance[i][j]/=size
    w=np.zeros((2,784), dtype=np.float) 
    eigvalue,eigvector=eig(covariance)
    eigvec=eigvector.transpose()
    
    
    idx = eigvalue.argsort()
    
    #eigvector=eigvector.transpose()
    eigvalue = eigvalue[idx]
    for i in range(2):
        w[i]=eigvec[idx[783-i]]
    
    
    z=[]
    for i in range(size):
        z.append((np.dot(w,train_data[i])).transpose())
    return z,w



size=int(input("size:"))
train_label,train_data,x_mean=read_file("X_train.csv","T_train.csv","train.txt",size)


test_label,test_data,xx_mean=read_file("X_test.csv","T_test.csv","test.txt",int(size/2))
y, x = svm_read_problem("train.txt")
yy,xx=svm_read_problem("test.txt")
m = svm_train(y,x,'-c 50')
p_label, p_acc, p_val = svm_predict(yy,xx, m)

z,w=pca(train_data,x_mean)

for i in range(size):
    if train_label[i]==1:
        plt.plot(z[i][0][0],z[i][0][1],'ro')
    if train_label[i]==2:
        plt.plot(z[i][0][0],z[i][0][1],'bo')
    if train_label[i]==3:
        plt.plot(z[i][0][0],z[i][0][1],'go')
    if train_label[i]==4:
        plt.plot(z[i][0][0],z[i][0][1],'co')
    if train_label[i]==5:
        plt.plot(z[i][0][0],z[i][0][1],'yo')
a=m.get_sv_indices()
for n in a:
    i=n-1
    if train_label[i]==1:
        plt.plot(z[i][0][0],z[i][0][1],'r*')
    if train_label[i]==2:
        plt.plot(z[i][0][0],z[i][0][1],'bs')
    if train_label[i]==3:
        plt.plot(z[i][0][0],z[i][0][1],'gp')
    if train_label[i]==4:
        plt.plot(z[i][0][0],z[i][0][1],'c+')
    if train_label[i]==5:
        plt.plot(z[i][0][0],z[i][0][1],'yx')
#plt.savefig("train_original.png")
plt.show()




zz=[]
for i in range(int(size/2)):
    zz.append((np.dot(w,test_data[i])).transpose())

for i in range(int(size/2)):
    if p_label[i]==1:
        plt.plot(zz[i][0][0],zz[i][0][1],'ro')
    if p_label[i]==2:
        plt.plot(zz[i][0][0],zz[i][0][1],'bo')
    if p_label[i]==3:
        plt.plot(zz[i][0][0],zz[i][0][1],'go')
    if p_label[i]==4:
        plt.plot(zz[i][0][0],zz[i][0][1],'co')
    if p_label[i]==5:
        plt.plot(zz[i][0][0],zz[i][0][1],'yo')
for n in a:
    i=n-1
    if train_label[i]==1:
        plt.plot(z[i][0][0],z[i][0][1],'r*')
    if train_label[i]==2:
        plt.plot(z[i][0][0],z[i][0][1],'bs')
    if train_label[i]==3:
        plt.plot(z[i][0][0],z[i][0][1],'gp')
    if train_label[i]==4:
        plt.plot(z[i][0][0],z[i][0][1],'c+')
    if train_label[i]==5:
        plt.plot(z[i][0][0],z[i][0][1],'yx')
        
#plt.savefig("test_original.png")
plt.show()



