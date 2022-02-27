compile_main:
	g++ -Wall -o out main.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_perceptron:
	g++ -Wall -o out perceptron.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_functions:
	g++ -Wall -o out functions.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_neuralnetwork:
	g++ -Wall -o out neuralnetwork.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_simpleNet:
	g++ -Wall -o out simpleNet.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
compile_twoLayerNet:
	g++ -Wall -o out twoLayerNet.cpp ./library/LinearAlgebra/* ./library/Plot/* ./library/DeepLearning/* -lm
run:
	./out