import Tkinter
import math
import time
vertices=[]
k=4
n=input()
m=input()
for i in range(0,2*n,2):
	c=raw_input().split(' ')
	x=int(c[0])
	y=int(c[1])
	x=x+250	
	y=250-y
	vertices.append((x,y))
circle=[]
with open('pro.txt','r') as F:
	i=0
	for line in F:
		if(i<n+2):
			i+=1
			continue
		attr=line.split(' ')
		print math.cos(float(attr[3])*3.14159265/180)
		x_c=float(attr[0])+float(attr[2])*math.cos(float(attr[3])*0.0175)
		y_c=float(attr[1])+float(attr[2])*math.sin(float(attr[3])*0.0175)
		x_c=x_c+250
		y_c=250-y_c
		r=float(attr[2])
		circle.append((x_c,y_c,r))
#print circle
top=Tkinter.Tk()

def quit():
	top.destroy()

C=Tkinter.Canvas(top,bg="white",height=500,width=500)
for x in vertices:
	C.create_oval(x[0]-5,x[1]-5,x[0]+5,x[1]+5,fill="green")

for (x,y,r) in circle:
	print x,y,r
	C.create_oval(x-r,y-r,x+r,y+r)
	C.pack()
	
top.mainloop()
