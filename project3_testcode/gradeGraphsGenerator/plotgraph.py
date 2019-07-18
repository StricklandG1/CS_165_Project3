import matplotlib
import matplotlib.pyplot as plt
import os.path


def plotImg(fname):
	f = open(fname+".txt","r");
	maxDeg = 50

	n = int(next(f));
	data = next(f).split();
	deg = []
	feq = []
	for i in range(n):
		deg.append(data[i*2])
		feq.append(data[i*2+1])

	fig, ax = plt.subplots()
	x = range(maxDeg+1)
	y = [0] * (maxDeg+1)

	for i, degree in enumerate(deg):
		degree = int(degree)
		if degree<=maxDeg:			
			y[degree] = int(feq[i])

	ax.scatter(x,y)

	ax.set(xlabel='degree', ylabel='frequency',
		title=fname)

	fig.savefig("img"+fname+".png")

if os.path.isfile("ddBarabasi.txt"):
	plotImg("ddBarabasi")
if os.path.isfile("ddErdos.txt"):
	plotImg("ddErdos")




