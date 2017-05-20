import Tkinter


n=input()
Vertices=[]
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
	Vertices.append(vertices)

def quit():
	top.destroy()

top=Tkinter.Tk()
C=Tkinter.Canvas(top,bg="white",height=500,width=500)
for vertices in Vertices:
	C.create_line(vertices,arrow=Tkinter.LAST)
C.pack()
top.mainloop()
