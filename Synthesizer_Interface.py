# Synthesizer Interface

import sys
import serial
import serial.tools.list_ports
from tkinter import *
from tkinter import messagebox

syn = Tk()
syn.geometry('900x260')
syn.title("Synthesizer") #Name of Projekt

mylabel=Label(text='------------------------------------------------------------------------------------------------------------------------')
mylabel.place(x=0,y=112)


#Connection -------------------------------------------------------------------------------------------------------------------------
ser = serial.Serial()
myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]   # searching the connented Port
m1 = myports[(0)]
m2 = m1[0]       # as an example m2 = 'COM4'

ser.baudrate = 460800
ser.port = m2
#ser
coport = Label(text=m2) # writing the connected Port on the window
coport.place(x=700,y=0)

# function definition
def connect():
    ser.open()   # opening the connected Port
    if ser.isOpen():
        show = Label(text="Connected    ")
    else:
        show = Label(text="Disconnected")
    show.place(x=700,y=50) 
    return

def disconnect():
    """ reset the values"""
    Osz_1(mvar1.set(0)) 
    Osz_2(mvar2.set(0))
    wave1(G1.set(0))
    wave2(G2.set(0))
    oct_1(G3.set(0))
    oct_2(G4.set(0))
    
    scale1.set(0)
    m1 = 'H3:{}T'.format(scale1.get())
    marr_1 = bytearray(m1, "ascii")
    ser.write(marr_1)
    
    scale2.set(5)
    m2 = 'H4:{}T'.format(scale2.get())
    marr_2 = bytearray(m2, "ascii")
    ser.write(marr_2)
    
    scale3.set(0)
    m3 = 'H5:{}T'.format(scale1.get())
    marr_3 = bytearray(m3, "ascii")
    ser.write(marr_3)
    
    scale4.set(5)
    m4 = 'H6:{}T'.format(scale4.get())
    marr_4 = bytearray(m4, "ascii")
    ser.write(marr_4)
    """-----"""
    ser.close()   # closeing the connected Port
    
    if ser.isOpen():
        show = Label(text="Connected    ")
    else:
        show = Label(text="Disconnected")
    show.place(x=700,y=50)
    return

b1 = Button(text="Connect",command=connect)   # Connect Button definition and placing
b1.place(x=700,y=20)

b2 = Button(text="Disconnent",command=disconnect)   # Disconnect Button definition and placing
b2.place(x=770,y=20)


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
# Variables definition for the Oscillators collection
mvar1=IntVar()
mvar2=IntVar()

# function definition
def Osz_1(*args):
    osz1_var=mvar1.get()
    if mvar1.get()==0 and mvar2.get()==0:
        ser.write(b'H0:0T')
    elif mvar1.get()==1 and mvar2.get()==0:
        ser.write(b'H0:1T')
    elif mvar1.get()==0 and mvar2.get()==1:
        ser.write(b'H0:2T')
    elif mvar1.get()==1 and mvar2.get()==1:
        ser.write(b'H0:3T')
    return

def Osz_2(*args):
    osz2_var=mvar2.get()
    if mvar1.get()==0 and mvar2.get()==0:
        ser.write(b'H0:0T')
    elif mvar1.get()==1 and mvar2.get()==0:
        ser.write(b'H0:1T')
    elif mvar1.get()==0 and mvar2.get()==1:
        ser.write(b'H0:2T')
    elif mvar1.get()==1 and mvar2.get()==1:
        ser.write(b'H0:3T')
    return

osz_1=Checkbutton(text="Oszillator 1:",state=ACTIVE, variable=mvar1, command=Osz_1)
osz_1.place(x=0,y=50)
osz_2=Checkbutton(text="Oszillator 2:",state=ACTIVE, variable=mvar2, command=Osz_2)
osz_2.place(x=0,y=160)


#Waves Collecting -------------------------------------------------------------------------------------------------------------------------
# Variables definition for the wave funktion collection - the value of each group of the buttons decide whether sine, rectangle, triangle or sawtooth function has been chosen
G1 = IntVar()
G2 = IntVar()

# function definition
def wave1(*args):     # sending the chosen value to the microcontroller
    wave1 = 'H1:{}T'.format(G1.get())   
    warr_1 = bytearray(wave1, "ascii")
    ser.write(warr_1)
    return

def wave2(*args):     # sending the chosen value to the microcontroller
    wave2 = 'H2:{}T'.format(G2.get())   
    warr_2 = bytearray(wave2, "ascii")
    ser.write(warr_2)
    return

sin1=Radiobutton(text="Sinus", value=0, variable=G1, command= wave1)
sin1.place(x=100,y=20)
Rechteck1=Radiobutton(text="Rechteck", value=1, variable=G1, command=wave1)
Rechteck1.place(x=100,y=40)
Dreieck1=Radiobutton(text="Dreieck", value=2, variable=G1, command=wave1)
Dreieck1.place(x=100,y=60)
Saegezahn1=Radiobutton(text="Sägezahn", value=3, variable=G1, command=wave1)
Saegezahn1.place(x=100,y=80)

sin2=Radiobutton(text="Sinus", value=0, variable=G2, command=wave2)
sin2.place(x=100,y=140)
Rechteck2=Radiobutton(text="Rechteck", value=1, variable=G2, command=wave2)
Rechteck2.place(x=100,y=160)
Dreieck2=Radiobutton(text="Dreieck", value=2, variable=G2, command=wave2)
Dreieck2.place(x=100,y=180)
Saegezahn2=Radiobutton(text="Sägezahn", value=3, variable=G2, command=wave2)
Saegezahn2.place(x=100,y=200)


#Octave collecting ------------------------------------------------------------------------------------------------------------------------
# writing and placing the section for Octave on the interface window
show_oct = Label(text="Oktave :")
show_oct.place(x=500,y=10)
show_oct = Label(text="Oktave :")
show_oct.place(x=500,y=130)

# Variables definition for Octave collection - the value of each group of the buttons decide which octave has been chosen
G3=IntVar()
G4=IntVar()

# function definition
def oct_1(*args):     # sending the chosen value to the microcontroller
    oct_1 = 'H7:{}T'.format(G3.get())  
    arr_1 = bytearray(oct_1, "ascii")
    ser.write(arr_1)
    return

def oct_2(*args):     # sending the chosen value to the microcontroller
    oct_2 = 'H8:{}T'.format(G4.get())  
    arr_2 = bytearray(oct_2, "ascii")
    ser.write(arr_2)
    return

oct_oszi1=Radiobutton(text="-2", value=-2, variable=G3, command=oct_1)
oct_oszi1.place(x=550,y=10)
oct_oszi1=Radiobutton(text="-1", value=-1, variable=G3, command=oct_1)
oct_oszi1.place(x=550,y=30)
oct_oszi1=Radiobutton(text="0", value=0, variable=G3, command=oct_1)
oct_oszi1.place(x=550,y=50)
oct_oszi1=Radiobutton(text="+1", value=1, variable=G3, command=oct_1)
oct_oszi1.place(x=550,y=70)
oct_oszi1=Radiobutton(text="+2", value=2, variable=G3, command=oct_1)
oct_oszi1.place(x=550,y=90)
oct_oszi2=Radiobutton(text="-2", value=-2, variable=G4, command=oct_2)
oct_oszi2.place(x=550,y=130)
oct_oszi2=Radiobutton(text="-1", value=-1, variable=G4, command=oct_2)
oct_oszi2.place(x=550,y=150)
oct_oszi2=Radiobutton(text="0", value=0, variable=G4, command=oct_2)
oct_oszi2.place(x=550,y=170)
oct_oszi2=Radiobutton(text="+1", value=1, variable=G4, command=oct_2)
oct_oszi2.place(x=550,y=190)
oct_oszi2=Radiobutton(text="+2", value=2, variable=G4, command=oct_2)
oct_oszi2.place(x=550,y=210)


#Frequency und Ampiltude -------------------------------------------------------------------------------------------------------------------
# function definition
def freq1(wert1):     # sending the chosen value to the microcontroller
    s1 = 'H3:{}T'.format(wert1)  
    arr1 = bytearray(s1, "ascii")
    ser.write(arr1)
    return
def amp1(wert2):     # sending the chosen value to the microcontroller
    s2 = 'H4:{}T'.format(wert2)   
    arr2 = bytearray(s2, "ascii")
    ser.write(arr2)
    return
def freq2(wert3):     # sending the chosen value to the microcontroller
    s3 = 'H5:{}T'.format(wert3)
    arr3 = bytearray(s3, "ascii")
    ser.write(arr3)
    return
def amp2(wert4):     # sending the chosen value to the microcontroller
    s4 = 'H6:{}T'.format(wert4)
    arr4 = bytearray(s4, "ascii")
    ser.write(arr4)
    return

scale1 = Scale(label="Frequenz",from_=0, to=16000, orient=HORIZONTAL, tickinterval=16000, command=freq1)
scale1.set(0)
scale1.place(x=220,y=10)

scale2 = Scale(label="Amplitude",from_=0, to=10, orient=HORIZONTAL,tickinterval=10, command=amp1)
scale2.set(5)
scale2.place(x=350,y=10)

scale3 = Scale(label="Frequenz",from_=0, to=16000, orient=HORIZONTAL,tickinterval=16000, command=freq2)
scale3.set(0)
scale3.place(x=220,y=130)

scale4 = Scale(label="Amplitude",from_=0, to=10, orient=HORIZONTAL,tickinterval=10, command=amp2)
scale4.set(5)
scale4.place(x=350,y=130)


#Entrybox -----------------------------------------------------------------------------------------------------------------------------
#limiting the entrybox content to only numbers
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

# function definition
def Eb_b1():     # sending the entrybox content to the microcontroller
    scale1.set(entry_box1.get())   # setting the frequeny sclae to the entrybox content
    e1 = 'H3:{}T'.format(entry_box1.get())   
    arr_e1 = bytearray(e1, "ascii")
    ser.write(arr_e1)
    return
def Eb_b2():     # sending the entrybox content to the microcontroller
    scale3.set(entry_box2.get())   # setting the frequeny sclae to the entrybox content
    e2 = 'H5:{}T'.format(entry_box1.get())
    arr_e2 = bytearray(e2, "ascii")
    ser.write(arr_e2)
    return

eb_b1 = Button(text="->",command=Eb_b1)
eb_b1.place(x=260,y=85)
eb_b2 = Button(text="->",command=Eb_b2)
eb_b2.place(x=260,y=205)


syn.mainloop()

