#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>

using namespace cv;
using namespace std;

#define MAP_CITY_MIN_AREA 50
#define MAP_CITY_MIN_CIRCULARITY 0.8

class Map{
    private:
    Mat map;
    vector<KeyPoint> cities_coords;
    vector< vector<double> > cities_dists;
    void calc_dist_lookup();
    void calc_cities_coords();
    void add_cities_to_map();

    public:
    Map();
    Map(string filename);
    void read_map_from_file(string filename);
    vector<KeyPoint> get_cities_coords();
    vector< vector<double> > get_cities_dists(); 
    void plot_map_route(vector<KeyPoint> ordered_cities, double scaling_factor);
};
