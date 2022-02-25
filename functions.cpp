#include<iostream>
#include<vector>
#include<math.h>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"
#include "./header/DeepLearning.hpp"
using namespace DeepLearning;

LinearAlgebra::Matrix test_function(LinearAlgebra::Vector x0, LinearAlgebra::Vector x1){
    LinearAlgebra::Matrix z({x0.size, x1.size}, 0, 1);
    for(int i = 0; i < x0.size; i++){
        for(int j = 0; j < x1.size; j++){
            z.array[i][j] = x0.array[i] * x0.array[i] + x1.array[j] * x1.array[j];
        }
    }
    return z;
}

float test_function2(float x0, float x1){
    return x0*x0 + x1*x1;
}

float test_function2_2(LinearAlgebra::Vector x){
    return x.dot(x);
}

int main(void){
    LinearAlgebra::Vector x = LinearAlgebra::arange(-5.0, 5.0, 0.1);
    LinearAlgebra::Vector y_step = Functions::Activation::step_function(x);
    LinearAlgebra::Vector y_sigmoid = Functions::Activation::sigmoid(x);

    Plot::PlotGraph plot("gnuplot -persist");
    plot.plot_start();
    plot.plot(x, y_step, {-6.0, 6.0}, {-0.1, 1.1}, {"x", "y"}, "red", false);
    plot.replot(x, y_sigmoid, "blue", false);
    plot.plot_end();

    LinearAlgebra::Vector y_ReLU = Functions::Activation::ReLU(x);
    plot.plot_start();
    plot.plot(x, y_ReLU, {-6.0, 6.0}, {-1.0, 5.5}, {"x", "y"}, "red", false);
    plot.plot_end();

    LinearAlgebra::Vector a = LinearAlgebra::array({1010, 1000, 990});
    LinearAlgebra::Vector softmax_a = Functions::Activation::softmax(a);
    a.show(); softmax_a.show();

    LinearAlgebra::Vector t = LinearAlgebra::array({0, 0, 1, 0, 0, 0, 0, 0, 0, 0});
    LinearAlgebra::Vector y1 = LinearAlgebra::array({0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0});
    LinearAlgebra::Vector y2 = LinearAlgebra::array({0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0});
    float ans;
    ans = Functions::Loss::sum_squared_loss(y1, t);
    std::cout << ans << "\n";
    ans = Functions::Loss::sum_squared_loss(y2, t);
    std::cout << ans << "\n";

    y1.show(); y2.show();
    ans = Functions::Loss::cross_entropy_loss(y1, t);
    std::cout << ans << "\n";
    ans = Functions::Loss::cross_entropy_loss(y2, t);
    std::cout << ans << "\n";

    float diff_value = Differential::numerical_differential([](float x){return 0.01*x*x + 0.1*x;}, 5);
    std::cout << diff_value << "\n";

    LinearAlgebra::Vector diff_x = LinearAlgebra::arange(0, 20, 0.1);
    LinearAlgebra::Vector diff_y = diff_x.map([](float x)->float{return 0.01*x*x + 0.1*x;});
    LinearAlgebra::Vector diff_y_end = diff_x.map([&diff_value](float x)->float{return diff_value * (x - 5) + 0.75;});
    plot.plot_start();
    plot.plot(diff_x, diff_y, {0, 20}, {0, 6}, {"x", "y"}, "red", false);
    plot.replot(diff_x, diff_y_end, "blue", false);
    plot.plot_end();

    LinearAlgebra::Vector x0 = LinearAlgebra::arange(-3, 3, 0.1);
    LinearAlgebra::Vector x1 = LinearAlgebra::arange(-3, 3, 0.1);
    LinearAlgebra::Matrix z = test_function(x0, x1);
    plot.plot_start();
    plot.plot_3d(test_function2_2, {-3, 3}, {-3, 3}, {0, 18}, {"x0", "x1", "f(x)"}, false, false, "red");
    plot.plot_end();
    
    Differential::numerical_gradient(test_function2_2, LinearAlgebra::array({3.0, 4.0})).show();
    Differential::numerical_gradient(test_function2_2, LinearAlgebra::array({0.0, 2.0})).show();
    Differential::numerical_gradient(test_function2_2, LinearAlgebra::array({3.0, 0.0})).show();

    x0 = LinearAlgebra::arange(-2.0, 2.25, 0.25);
    x1 = LinearAlgebra::arange(-2.0, 2.25, 0.25);
    std::vector<float> tmp_new_x0, tmp_new_x1;
    std::vector<LinearAlgebra::Vector> uv;
    for(int i = 0; i < x0.size; i++){
        for(int j = 0; j < x1.size; j++){
            uv.push_back(Differential::numerical_gradient(test_function2_2, LinearAlgebra::array({x0.array[i], x1.array[j]})));
            tmp_new_x0.push_back(x0.array[i]); tmp_new_x1.push_back(x1.array[j]);
        }
    }
    LinearAlgebra::Vector new_x0(tmp_new_x0), new_x1(tmp_new_x1);
    new_x0.show(); new_x1.show();
    LinearAlgebra::Matrix uv_matrix = Utils::get_matrix(uv);
    LinearAlgebra::Vector u = -1 * uv_matrix.get_vector(1, 0);
    LinearAlgebra::Vector v = -1 * uv_matrix.get_vector(1, 1);
    u.show(), v.show();

    plot.plot_start();
    plot.quiver(new_x0, new_x1, u, v, {-2.0, 2.0}, {-2.0, 2.0}, {"x0", "x1"});
    plot.plot_end();

    DeepLearning::Optimizer::gradient_descent(test_function2_2, LinearAlgebra::array({-3.0, 4.0}), 0.1, 100).show();
    return 0;
}