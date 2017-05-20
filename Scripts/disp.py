import Tkinter

vertices=[]

n=input()
for i in range(0,2*n,2):
	c=raw_input().split(' ')
	x=int(c[0])
	y=int(c[1])
	x=x+250	
	y=250-y
	vertices.append(x)
	vertices.append(y)
vertices.append(vertices[0])
vertices.append(vertices[1])
top=Tkinter.Tk()

def quit():
	top.destroy()

C=Tkinter.Canvas(top,bg="white",height=500,width=500)
C.create_line(vertices)
C.pack()
top.mainloop()
