echo "Run 30 seconds test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_30_segundos.txt 0.8 -cmp
echo "End test"

echo "Run 15 seconds test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_15_segundos.txt 0.5 -cmp
echo "End test"

echo "Run aleatorio test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_aleatorio.txt 0.76 -cmp
echo "End test"

echo "Run aleatorio desordenado test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_aleatorio_desordenado.txt 0.5 -cmp
echo "End test"

echo "Run completo test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_completo.txt 0.5 -cmp
echo "End test"

echo "Run sin links test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_sin_links.txt 0.5 -cmp
echo "End test"

echo "Run trivial test"
./tp1 /Users/pgarrett/Documents/facultad/metodos/labo/metnum/enunciado/tests/test_trivial.txt 0.3 -cmp
echo "End test"
