# Synthesizer Interface

import sys
import serial
import serial.tools.list_ports
from tkinter import *
from tkinter import messagebox

syn = Tk()
syn.geometry('700x260')
syn.title("Synthesizer") #Name of Projekt
#mylabel=Label(text='Synthesizer').pack()
mylabel=Label(text='-------------------------------------------------------------------------------------------')
mylabel.place(x=0,y=112)

#Connection -------------------------------------------------------------------------------------------------------------------------
ser = serial.Serial()

myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
#m1 = myports[(0)]
#m2 = m1[0]
m2 = 'COM4'

ser.baudrate = 460800
ser.port = m2
ser
coport = Label(text=m2)
coport.place(x=500,y=0)

def connect():
    ser.open()
    if ser.isOpen():
        show = Label(text="Connected    ")
    show.place(x=500,y=50)
    return

def disconnect():
    ser.close()
    show = Label(text="Disconnected")
    show.place(x=500,y=50)
    return

b1 = Button(text="Connect",command=connect)
b1.place(x=500,y=20)

b2 = Button(text="Disconnent",command=disconnect)
b2.place(x=570,y=20)



#Menu Construction -------------------------------------------------------------------------------------------------------------------------
def myAbout():
    messagebox.showinfo(title="About", message="Desigred by Jacob Ueltzen und Mohammad Dowah")
    return

menubar=Menu()
filemenu=Menu(menubar,tearoff=0)
filemenu.add_command(label="About", command=myAbout)
menubar.add_cascade(label="About",menu=filemenu)
syn.config(menu=menubar)



#Oszillators Checkbutton -----------------------------------------------------------------------------------------------------------------
mvar1=IntVar()
mvar2=IntVar()

def Osz_1():
    osz1_var=mvar1.get()
    if mvar1.get()==0 and mvar2.get()==0:
        ser.write(b'H0:0T')
    
    elif mvar1.get()==1 and mvar2.get()==0:
        ser.write(b'H0:1T')
    
    elif mvar1.get()==0 and mvar2.get()==1:
        ser.write(b'H0:2T')
    
    elif mvar1.get()==1 and mvar2.get()==1:
        ser.write(b'H0:3T')
    
    print(osz1_var)
    return
def Osz_2():
    osz2_var=mvar2.get()
    if mvar1.get()==0 and mvar2.get()==0:
        ser.write(b'H0:0T')
    elif mvar1.get()==1 and mvar2.get()==0:
        ser.write(b'H0:1T')
    elif mvar1.get()==0 and mvar2.get()==1:
        ser.write(b'H0:2T')
    elif mvar1.get()==1 and mvar2.get()==1:
        ser.write(b'H0:3T')
    
    print(osz2_var) 
    return
osz_1=Checkbutton(text="Oszillator 1:",state=ACTIVE, variable=mvar1, command=Osz_1)
osz_1.place(x=0,y=50)
osz_2=Checkbutton(text="Oszillator 2:",state=ACTIVE, variable=mvar2, command=Osz_2)
osz_2.place(x=0,y=160)




#Waves Collecting -------------------------------------------------------------------------------------------------------------------------
def wave1():
    ser.write(b'H0:4T')
    print('Sin') #here must be changed to collect the wave
    return
def wave2():
    ser.write(b'H0:5T')
    print('Rechteck') #here must be changed to collect the wave
    return
def wave3():
    ser.write(b'H0:6T')
    print('Dreieck') #here must be changed to collect the wave
    return
def wave4():
    ser.write(b'H0:7T')
    print('Sägezahn') #here must be changed to collect the wave
    return
    
sin1=Radiobutton(text="Sinus", value=1, variable='G1', command= wave1)
sin1.place(x=100,y=20)
Rechteck1=Radiobutton(text="Rechteck", value=2, variable='G1', command=wave2)
Rechteck1.place(x=100,y=40)
Dreieck1=Radiobutton(text="Dreieck", value=3, variable='G1', command=wave3)
Dreieck1.place(x=100,y=60)
Saegezahn1=Radiobutton(text="Sägezahn", value=4, variable='G1', command=wave4)
Saegezahn1.place(x=100,y=80)

sin2=Radiobutton(text="Sinus", value=5, variable='G2', command=wave1)
sin2.place(x=100,y=140)
Rechteck2=Radiobutton(text="Rechteck", value=6, variable='G2', command=wave2)
Rechteck2.place(x=100,y=160)
Dreieck2=Radiobutton(text="Dreieck", value=7, variable='G2', command=wave3)
Dreieck2.place(x=100,y=180)
Saegezahn2=Radiobutton(text="Sägezahn", value=8, variable='G2', command=wave4)
Saegezahn2.place(x=100,y=200)



#Frequenz und Ampiltude -------------------------------------------------------------------------------------------------------------------
def freq1(wert1):
    #x=wert1   
    s1 = 'H1:{}T'.format(wert1)
    arr1 = bytearray(s1, "ascii")
    ser.write(arr1)
    #print(wert1)
    return
def amp1(wert2):
    #ser.write(b'H2:358T')
    s2 = 'H2:{}T'.format(wert2)
    arr2 = bytearray(s2, "ascii")
    ser.write(arr2)
    #print(wert2)
    return
def freq2(wert3):
    #ser.write(b'H3:358T')
    s3 = 'H3:{}T'.format(wert3)
    arr3 = bytearray(s3, "ascii")
    ser.write(arr3)
    #print(wert3)
    return
def amp2(wert4):
    #ser.write(b'H4:358T')
    s4 = 'H4:{}T'.format(wert4)
    arr4 = bytearray(s4, "ascii")
    ser.write(arr4)
    #print(wert4)
    return

scale1 = Scale(label="Frequenz",from_=0, to=16000, orient=HORIZONTAL, tickinterval=16000, command=freq1)
scale1.set(0)
scale1.place(x=220,y=10)

scale2 = Scale(label="Amplitude",from_=0, to=10, orient=HORIZONTAL,tickinterval=10, command=amp1)
scale2.set(0)
scale2.place(x=350,y=10)

scale3 = Scale(label="Frequenz",from_=0, to=16000, orient=HORIZONTAL,tickinterval=16000, command=freq2)
scale3.set(0)
scale3.place(x=220,y=130)

scale4 = Scale(label="Amplitude",from_=0, to=10, orient=HORIZONTAL,tickinterval=10, command=amp2)
scale4.set(0)
scale4.place(x=350,y=130)


#Entrybox -----------------------------------------------------------------------------------------------------------------------------

def _checkNumberOnly(action, value_if_allowed):
    if action != '1':
        return True
    try:
        return value_if_allowed.isnumeric()
    except ValueError:
        return False

vcmd = (syn.register(_checkNumberOnly), '%d', '%P')
entry_box1 = Entry(width=5,validate='key', validatecommand=vcmd)
entry_box1.place(x=220,y=85)
entry_box2 = Entry(width=5,validate='key', validatecommand=vcmd)
entry_box2.place(x=220,y=205)

def Eb_b1():
    scale1.set(entry_box1.get())
    return
def Eb_b2():
    scale3.set(entry_box2.get())
    return

eb_b1 = Button(text="->",command=Eb_b1)
eb_b1.place(x=260,y=85)
eb_b2 = Button(text="->",command=Eb_b2)
eb_b2.place(x=260,y=205)



syn.mainloop()
