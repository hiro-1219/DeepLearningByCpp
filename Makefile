compile_main:
	g++ -Wall -o out main.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_perceptron:
	g++ -Wall -o out perceptron.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_funcions:
	g++ -Wall -o out functions.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_neuralnetwork:
	g++ -Wall -o out neuralnetwork.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
run:
	./out