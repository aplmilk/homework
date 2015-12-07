# -*- coding: utf-8 -*-
"""
Created on Sun Oct 27 22:51:11 2013

@author: lenovo
"""


def process():
    cv1=cv.create_rectangle([[140,75], [240, 175]],outline='black', width=1, fill='red')
    
from  Tkinter import*
root=Tk()
root.title('EX3.1')


label=Label(root,text='GUI wigets')
cv=Canvas(root,bg="white")
button=Button(root,text='Retangle',command=process)
entry=Entry(root,text = 'keyboard input here')


label.pack()
cv.pack()
button.pack()
entry.place(relx = 0.5,rely = 0.5,anchor = CENTER)

root.mainloop()