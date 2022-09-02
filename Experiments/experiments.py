import os

def generarCiclo(file, n):
    file.write(str(n) + "\n")
    file.write(str(n) + "\n")
    for page in range(1, n):
        file.write(str(page) + " " + str(page+1) + "\n")
    file.write(str(n) + " 1" + "\n")

def generarEstrellaQueApunteAUnaPaginaQueNoApunteANadie(file, n):
	file.write(str(n) + "\n")
	file.write(str(n-1) + "\n")
	for page in range(1,n-1):
		file.write(str(page) + " " + str(n-1) + "\n")
	file.write(str(n-1) + " " + str(n) + "\n")

def generarEstrellaVsClique(file, starSize, cliqueSize):
	totalNodes = starSize+cliqueSize
	file.write(str(totalNodes) + "\n")
	
	starLinks = starSize-1
	cliqueLinks = cliqueSize*(cliqueSize-1)
	inBetweenLinks = cliqueSize
	file.write(str(starLinks+cliqueLinks+inBetweenLinks) + "\n")
	
	#generate star links
	for page in range(1, starSize):
		file.write(str(page) + " " + str(starSize) + "\n")

	#generate in between links
	for page in range(starSize+1, totalNodes+1):
		file.write(str(starSize) + " " + str(page) + "\n")

	#generate cliqueLinks
	for i in range(starSize+1, totalNodes+1):
		for j in range(starSize+1, totalNodes+1):
			if i!=j:
				file.write(str(i) + " " + str(j) + "\n")

def generarCaminoLargoParaTestearP(file, n):
	file.write(str(n) + "\n")
	file.write(str(n-1) + "\n")
	for page in range(1, n):
		file.write(str(page) + " " + str(page+1) + "\n")

def testCiclo(smallestSize, largestSize):
	path = "./ciclo"
	if not os.path.exists(path):
		os.makedirs(path)

	for i in range(smallestSize, largestSize+1):
		output = open("./ciclo/ciclo_" + str(i) + ".txt", "w")
		generarCiclo(output, i)
		output.close()

def testEstrellaQueApunteAUnaPaginaQueNoApunteANadie(smallestSize, largestSize):
	path = "./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie"
	if not os.path.exists(path):
		os.makedirs(path)

	for i in range(smallestSize, largestSize+1):
		output = open("./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(i) + ".txt", "w")
		generarEstrellaQueApunteAUnaPaginaQueNoApunteANadie(output, i)
		output.close()

def testEstrellaVsCiclo(smallestSize, largestSize):
	path = "./estrella_vs_clique"
	if not os.path.exists(path):
		os.makedirs(path)

	for i in range(smallestSize, largestSize+1):
		for j in range(smallestSize, largestSize+1):
			output = open("./estrella_vs_clique/estrella_vs_clique_" + str(i) + "_" + str(j) + ".txt", "w")
			generarEstrellaVsClique(output, i, j)
			output.close()

def testCaminoLargoParaTestearP(smallestSize, largestSize):
	path = "./camino_largo_para_testear_p"
	if not os.path.exists(path):
		os.makedirs(path)

	for i in range(smallestSize, largestSize+1):
		output = open("./camino_largo_para_testear_p/camino_largo_para_testear_p_" + str(i) + ".txt", "w")
		generarCaminoLargoParaTestearP(output, i)
		output.close()

def generarTests(smallestSize, largestSize):
	testCiclo(smallestSize, largestSize)
	testEstrellaQueApunteAUnaPaginaQueNoApunteANadie(smallestSize, largestSize)
	testEstrellaVsCiclo(smallestSize, largestSize)
	testCaminoLargoParaTestearP(smallestSize, largestSize)

generarTests(3, 1000)


