import numpy as np

m = 10

x = np.linspace(-1, 1, m)
y = np.linspace(-1, 1, m)

X,Y = np.meshgrid(x, y)

vertices = []
connectivity = []

for i in range(m):
    for j in range(m):
        vertices.append([X[i,j], Y[i,j],0])
        if i < m-1 and j < m-1:
            # connectivity.append([i+j*m+m+1,i+j*m+m+2,i+j*m+2,i+j*m+1])
            connectivity.append([i+j*m+1,i+j*m+2,i+j*m+m+2,i+j*m+m+1])


with open("Assets/surface2.obj", "w") as f:
    
    f.write("o surface2\n")
    f.write("\n")

    for v in vertices:
        f.write("v {} {} {}\n".format(*v))

    f.write("\n")
    for c in connectivity:
        f.write("f {} {} {} {}\n".format(*c))

