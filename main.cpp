#include<iostream>
#include<vector>
#include<math.h>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"


LinearAlgebra::Matrix test_function(LinearAlgebra::Vector x, LinearAlgebra::Vector y){
    LinearAlgebra::Matrix z({x.size, y.size}, 0, 1);
    for(int i = 0; i < x.size; i++){
        for(int j = 0; j < x.size; j++){
            z.array[i][j] = sin(x.array[i]) * cos(y.array[j]);
        }
    }
    return z;
}


int main(void){
    LinearAlgebra::Vector a({1, 3, 5, 7, 9});
    LinearAlgebra::Vector b({2, 4, 6, 8, 10});
    LinearAlgebra::Vector add;
    float c;
    a.show(); b.show();
    add = a + b;
    c = a.dot(b);
    a.show();
    add.show();
    std::cout << c << "\n";

    LinearAlgebra::Matrix f({{1, 2, 3}, {4, 5, 6}});
    LinearAlgebra::Matrix g({{2, 3}, {5, 6}, {7, 8}});
    LinearAlgebra::Matrix l;
    f.show(); g.show();
    l = f.dot(g);
    l.show();

    LinearAlgebra::Matrix rand1({10, 10}, 0, 10);
    LinearAlgebra::Matrix rand2({10, 10}, 0, 10);
    LinearAlgebra::Matrix dot;
    rand1.show(); rand2.show();
    dot = rand1.dot(rand2);
    dot.show();

    LinearAlgebra::Matrix rand3({10, 1}, 0, 10);
    rand3.show();


    LinearAlgebra::Vector test1(10, 0, 10);
    LinearAlgebra::Matrix M_test1_1, M_test1_2;
    M_test1_1 = test1.vec_to_matrix(0);
    M_test1_2 = test1.vec_to_matrix(1);
    test1.show();
    M_test1_1.show(); M_test1_2.show();

    LinearAlgebra::Vector test2(10, 0, 10);
    LinearAlgebra::Vector test2_2;
    test2.show();
    test2_2 = test2 * 10;
    test2_2.show();

    test2_2 = test2 / 10;
    test2_2.show();

    test2_2 = 10 / test2;
    test2_2.show();

    LinearAlgebra::Matrix test3({10, 10}, 0, 10);
    LinearAlgebra::Matrix test3_2;
    test3.show();
    test3_2 = test3 * 10; test3_2.show();
    test3_2 = 10 * test3; test3_2.show();
    test3_2 = test3 / 10; test3_2.show();
    test3_2 = 10 / test3; test3_2.show();

    LinearAlgebra::Vector test4;
    test4 = LinearAlgebra::arange(0, 10, 0.1);
    test4.show();

    LinearAlgebra::Vector plot_x({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    LinearAlgebra::Vector plot_y({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    LinearAlgebra::Vector plot_y2({10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    LinearAlgebra::Vector plot_y3({1, 5, 2, 4, 5, 6, 1, 3, 5, 6});
    Plot::PlotGraph plot("gnuplot -persist");
    plot.plot_start();
    plot.plot(plot_x, plot_y, {0, 11}, {0, 11}, {"x", "y"});
    plot.replot(plot_x, plot_y2, "blue");
    plot.replot(plot_x, plot_y3, "green");
    plot.plot_end();

    LinearAlgebra::Vector scatter_x(50, 0, 10), scatter_y(50, 0, 10);
    plot.plot_start();
    plot.scatter(scatter_x, scatter_y, {0, 10}, {0, 10}, {"x", "y"});
    plot.plot_end();


    LinearAlgebra::Vector plot_z({-1, 0, 1, 0, -1, 0, 1, 0, -1, 0});
    plot.plot_start();
    plot.plot_3d(test_function, {0, 10}, {0, 10}, {-1, 1}, {"x", "y", "z"});
    plot.plot_3d(plot_x, plot_y, plot_z, {0, 10}, {0, 10}, {-1, 1}, {"x", "y", "z"}, false);
    plot.plot_end();

    LinearAlgebra::Vector array_test;
    array_test = LinearAlgebra::array({1, 2, 3, 4, 5});
    array_test.show();

    LinearAlgebra::Vector quiver_x({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    LinearAlgebra::Vector quiver_y({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    LinearAlgebra::Vector quiver_v, quiver_u;
    quiver_v = -0.2 * quiver_x;
    quiver_u = 0.1 * quiver_y;
    
    plot.plot_start();
    plot.quiver(quiver_x, quiver_y, quiver_u, quiver_v, {-1, 11}, {-1, 11}, {"x", "y"});
    plot.plot_end();

    LinearAlgebra::Vector testtest = LinearAlgebra::arange(0, 10, 1);
    float test_sum = testtest.sum();
    testtest.show();
    std::cout << test_sum << "\n";

    LinearAlgebra::Vector map_test({1, 2, 3, 4, 5, 6, 7, 8, 9});
    LinearAlgebra::Vector map_ans;
    map_ans = map_test.map([](float i)->float{return i > 3;});
    map_test.show(); map_ans.show();

    LinearAlgebra::Vector min_test({4, 3, 3, 5, 2});
    std::vector<float> min_ret = min_test.min();
    min_test.show();
    std::cout << min_ret[0] << ":" << min_ret[1] << "\n";

    LinearAlgebra::Vector max_test({4, 2, 6, 1, 5});
    std::vector<float> max_ret = max_test.max();
    max_test.show();
    std::cout << max_ret[0] << ":" << max_ret[1] << "\n";

    LinearAlgebra::Vector zero_test, one_test;
    zero_test = LinearAlgebra::zeros(10);
    one_test = LinearAlgebra::ones(10);
    zero_test.show();
    one_test.show();

    return 0;
}