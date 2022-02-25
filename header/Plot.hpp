#ifndef PLOT_HPP
#define PLOT_HPP
#include "error_type.hpp"
#include "LinearAlgebra.hpp"

namespace Plot{
    class PlotGraph{
    public:
        FILE *gp;
        const char* gnuplot_path;
        PlotGraph(const char* gnuplot_path);
        Error plot_start();
        Error plot_end();
        void plot(LinearAlgebra::Vector x, LinearAlgebra::Vector y, 
                  std::vector<float> x_range, std::vector<float> y_range, 
                  std::vector<const char*> label, const char* lc = "red", bool point = true);
        void replot(LinearAlgebra::Vector x, LinearAlgebra::Vector y, const char* lc = "red", bool point = true);
        void scatter(LinearAlgebra::Vector x, LinearAlgebra::Vector y,
                     std::vector<float> x_range, std::vector<float> y_range,
                     std::vector<const char*> label, const char* lc = "red");
        void plot_3d(float (*function)(float, float), 
                     std::vector<float> x_range, std::vector<float> y_range, std::vector<float> z_range,
                     std::vector<const char*> label, bool viewmap = false, bool colormap = false, const char* lc = "red");
        void plot_3d(LinearAlgebra::Matrix (*function)(LinearAlgebra::Vector, LinearAlgebra::Vector),
                     std::vector<float> x_range, std::vector<float> y_range, std::vector<float> z_range, 
                     std::vector<const char*> label, bool viewmap = false, bool colormap = false, const char* lc = "red");
        void plot_3d(float (*function)(LinearAlgebra::Vector), 
                     std::vector<float> x_range, std::vector<float> y_range, std::vector<float> z_range,
                     std::vector<const char*> label, bool viewmap = false, bool colormap = false, const char* lc = "red");
        void plot_3d(LinearAlgebra::Vector x, LinearAlgebra::Vector y, LinearAlgebra::Vector z,
                     std::vector<float> x_range, std::vector<float> y_range, std::vector<float> z_range,
                     std::vector<const char*> label, bool viewmap = false, const char* lc = "red", bool point = true);
        void quiver(LinearAlgebra::Vector x, LinearAlgebra::Vector y, LinearAlgebra::Vector u, LinearAlgebra::Vector v,
                    std::vector<float> x_range, std::vector<float> y_range, 
                    std::vector<const char*> label, const char* lc = "red");
    };
}

namespace Plot::GraphUtils{
    template<class Fn> LinearAlgebra::Matrix get_grid(Fn function, std::vector<float> x_range, std::vector<float> y_range){
        LinearAlgebra::Vector x = LinearAlgebra::arange(x_range[0], x_range[1], 0.1);
        LinearAlgebra::Vector y = LinearAlgebra::arange(y_range[0], y_range[1], 0.1);
        LinearAlgebra::Matrix z({x.size, y.size}, 0, 1);
        for(int i = 0; i < x.size; i++){
            for(int j = 0; j < y.size; j++){
                z.array[i][j] = function(x.array[i], y.array[j]);
            }
        }
        return z;
    }
}

#endif