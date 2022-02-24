#include<iostream>
#include<vector>
#include<math.h>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"
#include "./header/DeepLearning.hpp"
using namespace DeepLearning;

int main(void){
    LinearAlgebra::Vector x = LinearAlgebra::arange(-5.0, 5.0, 0.1);
    LinearAlgebra::Vector y_step = Functions::step_function(x);
    LinearAlgebra::Vector y_sigmoid = Functions::sigmoid(x);

    Plot::PlotGraph plot("gnuplot -persist");
    plot.plot_start();
    plot.plot(x, y_step, {-6.0, 6.0}, {-0.1, 1.1}, {"x", "y"}, "red", false);
    plot.replot(x, y_sigmoid, "blue", false);
    plot.plot_end();

    LinearAlgebra::Vector y_ReLU = Functions::ReLU(x);
    plot.plot_start();
    plot.plot(x, y_ReLU, {-6.0, 6.0}, {-1.0, 5.5}, {"x", "y"}, "red", false);
    plot.plot_end();
    return 0;
}