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
        void plot_3d(LinearAlgebra::Matrix (*function)(LinearAlgebra::Vector, LinearAlgebra::Vector),
                    std::vector<float> x_range, std::vector<float> y_range, std::vector<float> z_range, 
                    std::vector<const char*> label,  bool viewmap = false, bool colormap = false, const char* lc = "red");
    };
}

#endif