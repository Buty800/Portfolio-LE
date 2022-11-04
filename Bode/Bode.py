from tkinter import *
import matplotlib.pyplot as plt
import numpy as np

from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)


from matplotlib.figure import Figure


t = np.arange(0, 10, .01)

def tan(x):
    if x: return(np.maximum(0,t+1-np.log10(np.abs(x))) - np.maximum(0,t-1-np.log10(np.abs(x))))
    else: return(0*t+2)

def log(x):
    if x: return(np.maximum(0,t-np.log10(np.abs(x))))
    else: return(t)

def Bode(zeros, poles):
    s=0
   
    zeros = [20*log(zero) for zero in zeros]
    poles = [-20*log(pole) for pole in poles]
   
    return(poles+zeros)

def Phase(zeros, poles):
    s=0
   
    zeros = [45*tan(zero) for zero in zeros]
    poles = [-45*tan(pole) for pole in poles]
   
    return(poles+zeros)



def show():
    ax.clear()

    Ceros = [] if zeros.get() == "" else list(map(int, zeros.get().split(','))) 
    Polos = [] if poles.get() == "" else list(map(int, poles.get().split(',')))

    if select.get() and (not comps.get()):
        s = sum(Phase(Ceros, Polos))  
        ax.plot(t, s)
        ax.set(xlabel='ω (rad/seg)', ylabel='φ (°)', title='Bode graph')
       

    if (not select.get()) and (not comps.get()):
        s = sum(Bode(Ceros, Polos))  
        ax.plot(t, s)
        ax.set(xlabel='ω (rad/seg)', ylabel='Av (°)', title='Bode graph')

   
    if select.get() and comps.get():
        for comp in Phase(Ceros, Polos):
            s = comp
            ax.plot(t,s)
            ax.set(xlabel='ω (rad/seg)', ylabel='φ (°)', title='Bode graph')
           
 

    if (not select.get()) and comps.get():
        for comp in Bode(Ceros, Polos):
            s = comp
            ax.plot(t,s)
            ax.set(xlabel='ω (rad/seg)', ylabel='Av (°)', title='Bode graph')

    ax.grid()
    canvas.draw()

   


Root = Tk()


comps = IntVar()
select = IntVar()

zeros = Entry(Root)
zeros.pack(side=LEFT)
poles = Entry(Root)
poles.pack(side=LEFT)


Radiobutton(Root, text="Bode", variable=select, value=0, command=show).pack(side=LEFT)
Radiobutton(Root, text="Phase",variable=select, value=1, command=show).pack(side=LEFT)

Checkbutton(Root, text="See components", variable=comps, command=show).pack()

fig = Figure(figsize=(5, 4), dpi=100)
ax = fig.add_subplot()
ax.grid()
canvas = FigureCanvasTkAgg(fig, master=Root)  
canvas.get_tk_widget().pack(side=RIGHT, fill=BOTH, expand=True)


Root.mainloop()
