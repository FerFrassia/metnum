import subprocess as sub
import config as c
import matplotlib.pyplot as plt

f = plt.figure()
f.set_figwidth(10)
f.set_figheight(6)

def runTests():
	print("Corriendo test")
	for i in range(c.minNodes, c.maxNodes):
	    sub.run("./tp1 " + path + filename + str(i) + ".txt " + str(c.p), shell=True)

def readApproximations(path, filename):
	res = []
	for n in range(c.minNodes, c.maxNodes):
		file = open(path + filename + str(n) + ".txt.aprox.out", "r")
		lines = file.readlines()
		for i, line in enumerate(lines):
			if (i == 1):
				# leer solo segunda linea
				res.append(float(line))
	return res

def generateGraph():
	denso = readApproximations("./aprox/grafo_denso/", "grafo_denso_")
	control = readApproximations("./aprox/grafo_control/", "grafo_control_")
	ralo = readApproximations("./aprox/grafo_ralo/", "grafo_ralo_")

	x = list(range(c.minNodes, c.maxNodes))
	plt.xlabel("Número de páginas")
	plt.ylabel("Error aproximado")
	plt.plot(x, denso, color="red", label="grafo denso")
	plt.plot(x, ralo, color="blue", label="grafo ralo")
	plt.plot(x, control, color="orange", label="grafo control")
	plt.legend()
	plt.show()

path = "./aprox/grafo_denso/"
filename = "grafo_denso_"

#runTests()
generateGraph()