import Tkinter
Vertices=[]
original=[]
for __i in range(0,3):
	n=input()
	for i in range(0,2*n,2):
		vertices=[]
		for z in range(0,2):
			c=raw_input().split(' ')
			x=float(c[0])
			y=float(c[1])
			x=x+250	
			y=250-y
			vertices.append(x)
			vertices.append(y)
		if(__i==0 or __i==1):
			Vertices.append(vertices)
		else:
			original.append(vertices)

def quit():
	top.destroy()

top=Tkinter.Tk()
C=Tkinter.Canvas(top,bg="white",height=500,width=500)
for vertices in Vertices:
	C.create_line(vertices,)
for ori in original:
	C.create_line(ori,arrow=Tkinter.LAST,width=3.5)
C.pack()
top.mainloop()