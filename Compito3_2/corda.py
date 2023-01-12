
import numpy as np
import sys
import matplotlib.pyplot as plt
from ROOT import *
import time


plt.ion()
fig=plt.figure()
ax=plt.subplot()

def main(*arg):
     #parametri fisici
     
     L=5 #metri lunghezza corda
     T=1000 #tensione corda
     
     tmax=5
     t=0
     A=2 #Ampiezza sinusoide
     k=2*np.pi/L


     #soluzione equazione delle onde
     def rho(x): return 1+x**2
     
     def initial_condition(function):
          
          x=np.linspace(0,L,N)
          
          if function=="sine":
               u=np.sin(2*np.pi*(3/L)*x)
          
          elif function=="gauss":
               sigma=0.1
               mu=L/2
               u=A*(1/np.sqrt(2*np.pi*sigma))*np.exp(-(x-mu)**2/(2*sigma**2))
          
          else :
               print("Condizione iniziale non implementata")
               sys.exit()
          
          u[0]=0
          u[N-1]=0
          return u
     
     

     #discretizzazione
     N=501
     x=np.linspace(0,L,N)
     dx=x[1]-x[0]
     dt=0.0001


     vp=dx/dt
     v_const=0.5*vp
     V=np.sqrt(T/rho(x))

     if(vp<v_const or any(vp<V) ):
          print("Stabilita non garantita")
          sys.exit()
          
     u=np.zeros(N)
     u=np.copy(initial_condition(arg[1]))
     u_old=np.copy(u)
     u_new=np.copy(u)

     i=0
     bb,=ax.plot(x,u)     
          
     if(arg[0]=="densita_const"):
     
               u_new[N-1]=0
               u_new[0]=0
               u_new[1:N-1]=u[1:N-1]+((v_const/vp)**2)*(u[2:N]+u[0:N-2]-2*u[1:N-1])
               u_old=np.copy(u)
               u=np.copy(u_new)
               
               for t in np.arange(0,tmax,dt):
                    u_new[N-1]=0
                    u_new[0]=0
                    u_new[1:N-1]=2*u[1:N-1]-u_old[1:N-1]+((v_const/vp)**2)*(u[2:N]+u[0:N-2]-2*u[1:N-1])
                    u_old=np.copy(u)
                    u=np.copy(u_new)        
                    i+=1    
                    if(not i%5):
                         plt.ylim(-2*A,2*A)
                         plt.xlim(0,L)
                         bb.set_xdata(x)
                         bb.set_ydata(u_new)
                         
                         fig.canvas.flush_events()
                         time.sleep(0.1)
                         
          
                         
                    
                    
     
     elif(arg[0]=="densita_variabile"):

          u_new[N-1]=0
          u_new[0]=0
          u_new[1:N-1]=u[1:N-1]+((V[1:N-1]/vp)**2)*(u[2:N]+u[0:N-2]-2*u[1:N-1])
          u_old=np.copy(u)
          u=np.copy(u_new)
          for t in np.arange(0,tmax,dt):
               u_new[N-1]=0
               u_new[0]=0
               u_new[1:N-1]=2*u[1:N-1]-u_old[1:N-1]+((V[1:N-1]/vp)**2)*(u[2:N]+u[0:N-2]-2*u[1:N-1])
               u_old=np.copy(u)
               u=np.copy(u_new)        
               i+=1
               if(not i%5):
                    plt.ylim(-2*A,2*A)
                    plt.xlim(0,L)
                    bb.set_xdata(x)
                    bb.set_ydata(u_new)
                    ax.relim()
                    fig.canvas.flush_events()
                    time.sleep(0.1)
                         
          
   
    
               

    
#if __name__ == '__main__':
main("densita_const","sine")    
    
