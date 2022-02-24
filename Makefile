compile_main:
	g++ -Wall -o out main.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_perceptron:
	g++ -Wall -o out perceptron.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm