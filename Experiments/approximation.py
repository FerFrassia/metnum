import subprocess as sub
import config as c

def runCiclo():
	print("Corriendo test: Ciclo")
	for i in range(c.minNodes, c.maxNodes+1, 50):
	    sub.run("./tp1 ./enunciado/ciclo/ciclo_" + str(i) + ".txt " + str(c.p), shell=True)

def runTests():
	print("Corriendo tests")
	runCiclo()
	print("Tests corridos")

runTests()