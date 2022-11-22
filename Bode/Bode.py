import math
from tkinter import *
import matplotlib.pyplot as plt
import numpy as np

from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)


from matplotlib.figure import Figure


def on_focus_in(entry):
    if entry.cget('state') == 'disabled':
        entry.configure(state='normal')
        entry.delete(0, 'end')

def on_focus_out(entry, placeholder):
    if entry.get() == "":
        entry.insert(0, placeholder)
        entry.configure(state='disabled')

t = np.arange(0, 10, .01)

def tan(x):
    if x: return(np.maximum(0,t+1-np.log10(np.abs(x))) - np.maximum(0,t-1-np.log10(np.abs(x))))
    else: return(0*t+2)

def log(x):
    if x: return(np.maximum(0,t-np.log10(np.abs(x))))
    else: return(t)

def Bode(zeros, poles, lin):
   
    zeros = [20*log(zero) for zero in zeros]
    poles = [-20*log(pole) for pole in poles]
    
    res = poles+zeros
    res.append(0*t+20*np.log10(np.abs(lin)))
    return(res)

def Phase(zeros, poles):

    zeros = [45*tan(zero) for zero in zeros]
    poles = [-45*tan(pole) for pole in poles]
   
    return(poles+zeros)



def show():
    ax.clear()

    Lin = 1 if lin.get() == "" or lin.get() == "Lineal" else float(lin.get())
    Ceros = [] if zeros.get() == "" or zeros.get() == "Ceros" else list(map(float, zeros.get().split(','))) 
    Polos = [] if poles.get() == "" or poles.get() == "Polos" else list(map(float, poles.get().split(',')))

    if select.get() and (not comps.get()):
        s = sum(Phase(Ceros, Polos))  
        ax.plot(t, s)
        ax.set(xlabel='ω (rad/seg)', ylabel='φ (°)', title='Grafico de Bode')
       

    if (not select.get()) and (not comps.get()):
        s = sum(Bode(Ceros, Polos, Lin))  
        ax.plot(t, s)
        ax.set(xlabel='ω (rad/seg)', ylabel='Av (db)', title='Grafico de Bode')

   
    if select.get() and comps.get():
        for comp in Phase(Ceros, Polos):
            s = comp
            ax.plot(t,s)
            ax.set(xlabel='ω (rad/seg)', ylabel='φ (°)', title='Grafico de Bode')
           
 

    if (not select.get()) and comps.get():
        for comp in Bode(Ceros, Polos, Lin):
            s = comp
            ax.plot(t,s)
            ax.set(xlabel='ω (rad/seg)', ylabel='Av (db)', title='Grafico de Bode')

    #ax.set_xticks(np.arange(0, 11, 1))
    #ax.set_yticks(np.arange(math.ceil(min(s)/10)*10, math.ceil(max(s)/10)*10, 10))
    ax.grid()
    canvas.draw()
    

   


Root = Tk()


comps = IntVar()
select = IntVar()

lin = Entry(Root)

lin.pack(side=LEFT)
lin.insert(0, "Lineal")
lin.configure(state='disabled')

lin_focus_in = lin.bind('<Button-1>', lambda x: on_focus_in(lin))
lin_focus_out = lin.bind('<FocusOut>', lambda x: on_focus_out(lin, 'Lineal'))

zeros = Entry(Root)
zeros.pack(side=LEFT)
zeros.insert(0, "Ceros")
zeros.configure(state='disabled')

zeros_focus_in = zeros.bind('<Button-1>', lambda x: on_focus_in(zeros))
zeros_focus_out = zeros.bind('<FocusOut>', lambda x: on_focus_out(zeros, 'Ceros'))


poles = Entry(Root)
poles.pack(side=LEFT)
poles.insert(0, "Polos")
poles.configure(state='disabled')

poles_focus_in = poles.bind('<Button-1>', lambda x: on_focus_in(poles))
poles_focus_out = poles.bind('<FocusOut>', lambda x: on_focus_out(poles, 'Polos'))




Radiobutton(Root, text="Bode", variable=select, value=0, command=show).pack(side=LEFT)
Radiobutton(Root, text="Phase",variable=select, value=1, command=show).pack(side=LEFT)

Checkbutton(Root, text="Ver componentes", variable=comps, command=show).pack()

fig = Figure(figsize=(5, 4), dpi=100)
ax = fig.add_subplot()
ax.grid()
canvas = FigureCanvasTkAgg(fig, master=Root)  
canvas.get_tk_widget().pack(side=RIGHT, fill=BOTH, expand=True)


Root.mainloop()
