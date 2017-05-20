import Tkinter

vertices=[]

n=input()
for i in range(0,2*n,2):
	c=raw_input().split(' ')
	x=int(c[0])
	y=int(c[1])
	x=x+250	
	y=250-y
	vertices.append((x,y))

top=Tkinter.Tk()

def quit():
	top.destroy()

C=Tkinter.Canvas(top,bg="white",height=500,width=500)
for x in vertices:
	C.create_oval(x[0]-1,x[1]-1,x[0]+1,x[1]+1,fill="green")
C.pack()
top.mainloop()
