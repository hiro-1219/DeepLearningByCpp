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
        fprintf(this->gp, "set multiplot\n");
        fprintf(this->gp, "unset key\n");
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
        //fprintf(gp, "replot title \"%s\"\n", title);
        if(point == true) fprintf(this->gp, "plot '-' with linespoints lc rgb \"%s\"\n", lc);
        else if(point == false) fprintf(this->gp, "plot '-' with lines lc rgb \"%s\"\n", lc);
        for(int i = 0; i < x.size; i++){
            fprintf(this->gp, "%f\t%f\n", x.array[i], y.array[i]);
        }
        fprintf(this->gp, "e\n");
    }
    
}