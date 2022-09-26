import subprocess as sub
import config as c
import matplotlib.pyplot as plt

f = plt.figure()
f.set_figwidth(10)
f.set_figheight(6)

def epsilonTests(eps):
	print("Corriendo test epsilon")
	for i in range(c.minNodes, c.maxNodes):
	    sub.run("./tp1 " "aprox/epsilon/10-" + str(eps) + "/grafo_control_" + str(i) + ".txt " + str(c.p) + " " + str(eps), shell=True)

def densityTests(path, filename):
	print("Corriendo test densidad")
	for i in range(c.minNodes, c.maxNodes):
	    sub.run("./tp1 " + path + filename + str(i) + ".txt " + str(c.p), shell=True)

def probabilityTests(p):
	print("Corriendo test probabilidad")
	for i in range(c.minNodes, c.maxNodes):
	    sub.run("./tp1 " + "./aprox/" + "p" + str(int(p*100)) + "/grafo_ralo_" + str(i) + ".txt " + str(p), shell=True)

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

def generateDensityGraph():
	denso = readApproximations("./grafo_denso/", "grafo_denso_")
	control = readApproximations("./grafo_control/", "grafo_control_")
	ralo = readApproximations("./grafo_ralo/", "grafo_ralo_")

	x = list(range(c.minNodes, c.maxNodes))
	plt.xlabel("Número de páginas")
	plt.ylabel("Error aproximado")
	plt.plot(x, denso, color="red", label="grafo denso")
	plt.plot(x, ralo, color="blue", label="grafo ralo")
	plt.plot(x, control, color="orange", label="grafo control")
	plt.legend()
	plt.show()

def generateProbabilityGraph():
	p25 = readApproximations("./aprox/p25/", "grafo_denso_")
	p50 = readApproximations("./aprox/p50/", "grafo_denso_")
	p75 = readApproximations("./aprox/p75/", "grafo_denso_")
	p90 = readApproximations("./aprox/p90/", "grafo_denso_")

	x = list(range(c.minNodes, c.maxNodes))
	plt.xlabel("Número de páginas")
	plt.ylabel("Error aproximado")
	plt.plot(x, p25, color="red", label="prob: 25%")
	plt.plot(x, p50, color="orange", label="prob: 50%")
	plt.plot(x, p75, color="green", label="prob: 75%")
	plt.plot(x, p90, color="blue", label="prob: 90%")
	plt.legend()
	plt.show()

densities = ["grafo_denso", "grafo_control", "grafo_ralo"]
probs = [0.25, 0.50, 0.75, 0.90]
eps = [2, 3, 4, 5, 6]

def runProbabilityTests():
	for prob in probs:
		probabilityTests(prob)

def runDensityTests():
	for density in densities:
		path = "./" + density + "/"
		filename = density + "_"
		densityTests(path, filename)

def runEpsilonTests():
	for e in eps:
		epsilonTests(e)

runProbabilityTests()
runDensityTests()
runEpsilonTests()

generateProbabilityGraph()
generateDensityGraph()