#include<iostream>
#include<vector>
#include<string>
#include "../../header/error_type.hpp"
#include "../../header/Plot.hpp"
#include "../../header/LinearAlgebra.hpp"

namespace Plot{
    PlotGraph::PlotGraph(const char* gnuplot_path){
        this->gnuplot_path = gnuplot_path;
    }

    Error PlotGraph::plot_start(){
        this->gp = popen(this->gnuplot_path, "w");
        if(this->gp == NULL){
            std::cout << "Error occurred by popen()" << "\n";
            return E_IO_ERROR_OPEN_FILE;
        }
        std::cout << "Graph plot start" << "\n";
        fprintf(this->gp, "set multiplot\n");
        fprintf(this->gp, "unset key\n");
        return E_SUCCESS;
    }

    Error PlotGraph::plot_end(){
        int error = pclose(this->gp);
        if(error == -1){
            std::cout << "Error occurred by pclose()" << "\n";
            return E_IO_ERROR;
        }
        this->gp = NULL;
        std::cout << "Graph plot end" << "\n";
        return E_SUCCESS;
    }

    void PlotGraph::plot(LinearAlgebra::Vector x, LinearAlgebra::Vector y, 
                         std::vector<float> x_range, std::vector<float> y_range, 
                         std::vector<const char*> label, const char* lc, bool point){
        fprintf(this->gp, "set xrange [%f:%f]\n", x_range[0], x_range[1]);
        fprintf(this->gp, "set yrange [%f:%f]\n", y_range[0], y_range[1]);
        fprintf(this->gp, "set xlabel \"%s\"\n", label[0]);
        fprintf(this->gp, "set ylabel \"%s\"\n", label[1]);
        if(point == true) fprintf(this->gp, "plot '-' with linespoints lc rgb \"%s\"\n", lc);
        else if(point == false) fprintf(this->gp, "plot '-' with lines lc rgb \"%s\"\n", lc);
        for(int i = 0; i < x.size; i++){
            fprintf(this->gp, "%f %f\n", x.array[i], y.array[i]);
        }
        fprintf(this->gp, "e\n");
    }

    void PlotGraph::replot(LinearAlgebra::Vector x, LinearAlgebra::Vector y, const char* lc, bool point){
        if(point == true) fprintf(this->gp, "plot '-' with linespoints lc rgb \"%s\"\n", lc);
        else if(point == false) fprintf(this->gp, "plot '-' with lines lc rgb \"%s\"\n", lc);
        for(int i = 0; i < x.size; i++){
            fprintf(this->gp, "%f %f\n", x.array[i], y.array[i]);
        }
        fprintf(this->gp, "e\n");
    }
    
    void PlotGraph::scatter(LinearAlgebra::Vector x, LinearAlgebra::Vector y, 
                            std::vector<float> x_range, std::vector<float> y_range,
                            std::vector<const char*> label, const char* lc){
        fprintf(this->gp, "set xrange [%f:%f]\n", x_range[0], x_range[1]);
        fprintf(this->gp, "set yrange [%f:%f]\n", y_range[0], y_range[1]);
        fprintf(this->gp, "set xlabel \"%s\"\n", label[0]);
        fprintf(this->gp, "set ylabel \"%s\"\n", label[1]);
        fprintf(this->gp, "plot '-' with points pt 7 lc rgb \"%s\"\n", lc);
        for(int i = 0; i < x.size; i++){
            fprintf(this->gp, "%f %f\n", x.array[i], y.array[i]);
        }
        fprintf(this->gp, "e\n");
    }

    void PlotGraph::plot_3d(LinearAlgebra::Matrix (*function)(LinearAlgebra::Vector, LinearAlgebra::Vector),
                            std::vector<float> x_range, std::vector<float> y_range, std::vector<float> z_range,
                            std::vector<const char*> label, bool viewmap, bool colormap, const char* lc){
        fprintf(this->gp, "set dgrid3d smooth csplines\n");
        fprintf(this->gp, "set hidden3d\n");
        fprintf(this->gp, "set xrange [%f:%f]\n", x_range[0], x_range[1]);
        fprintf(this->gp, "set yrange [%f:%f]\n", y_range[0], y_range[1]);
        fprintf(this->gp, "set zrange [%f:%f]\n", z_range[0], z_range[1]);
        fprintf(this->gp, "set xlabel \"%s\"\n", label[0]);
        fprintf(this->gp, "set ylabel \"%s\"\n", label[1]);
        fprintf(this->gp, "set zlabel \"%s\"\n", label[2]);
        if(viewmap == true) fprintf(this->gp, "set view map\n");
        if(colormap == true) fprintf(this->gp, "set pm3d\n");
        fprintf(this->gp, "splot '-' using 1:2:3 with lines ");
        if(colormap == true) fprintf(this->gp, "\n");
        else if(colormap == false) fprintf(this->gp, "lc rgb \"%s\"\n", lc);
        LinearAlgebra::Vector x, y;
        LinearAlgebra::Matrix z;
        x = LinearAlgebra::arange(x_range[0], x_range[1], 0.1);
        y = LinearAlgebra::arange(y_range[0], y_range[1], 0.1);
        z = function(x, y);
        for(int i = 0; i < x.size; i++){
            for(int j = 0; j < y.size; j++){
                fprintf(this->gp, "%f %f %f\n", x.array[i], y.array[j], z.array[i][j]);
            }
            fprintf(this->gp, "\n");
        }
        fprintf(this->gp, "e\n");
    }
}