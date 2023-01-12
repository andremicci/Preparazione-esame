
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import sys
from ROOT import *
from mpl_toolkits.mplot3d import Axes3D
plt.ion()
#Soluzione equazione di poisson


V0=400 #volt
N=51
V=np.ones((N,N))*1/V0
V_tmp=np.copy(V)
V_new=np.copy(V)

V[15:35,20]=1
V[15:35,30]=-1


Delta=np.ones((N,N))*10
ea=0.01
er=ea

fig=plt.figure()
fig.tight_layout()

ax = fig.add_subplot(111, projection="3d")
x=np.linspace(0,5,N)
y=np.linspace(0,5,N)
X,Y=np.meshgrid(x,y)

#ax.plot_surface(X,Y,V)


statement=(Delta > ea+np.abs(V)*er).all

while statement:

    
    V_tmp=np.matrix(np.zeros((N,N)))
    V=np.copy(V_new)
    

    
    for i in range(1,N-1):
        for j in range(1,N-1):
            
           V_tmp[i,j]=0.25*(V[i+1,j]+V[i-1,j]+V[i,j+1]+V[i,j-1])
           V_tmp[15:35,20]=1
           V_tmp[15:35,30]=-1
    
           
    V_new=np.copy(V_tmp)
    Delta=np.copy(np.abs(V-V_new))
    Delta[15:35,20]=0
    Delta[15:35,30]=0
    
    #Delta=np.zeros((N,N))
    #for i in range(1,N-1):
     #   for j in range(1,N-1):
      #      Delta[i,j]=np.abs(V[i,j]-V_new[i,j])

    
    
    ax.plot_surface(X,Y,V_new,color='r')
    
    fig.canvas.flush_events()
    plt.pause(0.0001)
    
    

print("Rilassamento raggiunto!")
sys.exit()




    
        
        
