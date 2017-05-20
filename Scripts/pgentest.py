import Tkinter
top=Tkinter.Tk()
vertices=[]
C=Tkinter.Canvas(top,bg="white",height=500,width=500)
def quit():
	top.destroy()

def getPoints(event):
	vertices.append(event.x)
	vertices.append(event.y)
	#print event.x-250, 250-event.y
	C.create_oval(event.x-1,event.y-1,event.x+1,event.y+1,fill="red")


C.bind("<Button-1>",getPoints)
C.pack()
top.mainloop()
print len(vertices)/2-1
i=0
vertices[len(vertices)-1]=vertices[1]
vertices[len(vertices)-2]=vertices[0]
for x in vertices:
	if(i==len(vertices)-2):
		break;
	if(i%2==0):
		print x-250,
	else:
		print 250-x 
	i+=1