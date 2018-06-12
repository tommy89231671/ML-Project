import matplotlib.pyplot as plt
from numpy.linalg import eig
import numpy as np





def read_file(X_name,T_name,size):
    X=open(X_name,"r")
    T=open(T_name,"r")
    label=[]
    data=[]
    x_mean=np.zeros((784,1), dtype=np.float)
    #file=fp.read()
    for i in range(size):
        line=X.readline()
        label.append(int(T.readline()))
    
        x=np.zeros((784,1), dtype=np.float)
        e=0
        for j in range(783):
            end=line.find(',',e)
            x[j]=float(line[e:end])
            x_mean[j]+=(x[j]/size)
            e=end+1
        end=line.find('\n')
        x[783]=float(line[e:end])
        data.append(x)
    return label,data,x_mean    
            
         


train_label=[]
train_data=[]
x_mean=np.zeros((784,1), dtype=np.float)        

size=int(input("size:"))

train_label,train_data,x_mean=read_file("X_train.csv","T_train.csv",size)

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
plt.show()


test_label=[]
test_data=[]
size=int(size/2)
test_label,test_data,xx_mean=read_file("X_test.csv","T_test.csv",size)



zz=[]
for i in range(size):
    zz.append((np.dot(w,test_data[i])).transpose())

for i in range(size):
    if test_label[i]==1:
        plt.plot(zz[i][0][0],zz[i][0][1],'ro')
    if test_label[i]==2:
        plt.plot(zz[i][0][0],zz[i][0][1],'bo')
    if test_label[i]==3:
        plt.plot(zz[i][0][0],zz[i][0][1],'go')
    if test_label[i]==4:
        plt.plot(zz[i][0][0],zz[i][0][1],'co')
    if test_label[i]==5:
        plt.plot(zz[i][0][0],zz[i][0][1],'yo')
plt.show()
#d=eigvalue[782]*eigvec[idx[782]].transpose()
#
#e=np.dot(covariance,eigvec[idx[782]])




#fp=open("X_test.csv","r")

    