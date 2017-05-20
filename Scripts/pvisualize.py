import Tkinter
Vertices=[]
for __i in range(0,2):
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
		Vertices.append(vertices)

def quit():
	top.destroy()

top=Tkinter.Tk()
C=Tkinter.Canvas(top,bg="white",height=500,width=500)
for vertices in Vertices:
	C.create_line(vertices,arrow=Tkinter.LAST)
C.pack()
top.mainloop()
'''
7
-25 129
-159 -9
-123 -138
26 -161
58 -40
-64 -33
-22 40
'''
'''
7
25 162
-172 42
-131 -118
-11 10
111 -70
169 93
67 104
'''
'''
9
3 136
-147 14
-153 -157
9 -37
-99 -9
41 101
32 18
170 86
96 178
'''
