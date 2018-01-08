#include "Map.h"

// Private functions
void Map::calc_cities_coords(){
    Mat map_gray;
    cvtColor(map, map_gray, CV_BGR2GRAY);
    GaussianBlur(map_gray, map_gray, Size( 3, 3), 0, 0 );

    //Setup paramters for blob detection. 
    SimpleBlobDetector::Params params;

    params.filterByArea = true;
    params.filterByCircularity = true;
    params.minArea = MAP_CITY_MIN_AREA;
    params.minCircularity = MAP_CITY_MIN_CIRCULARITY;

    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
    detector->detect(map_gray, cities_coords);
}

void Map::add_cities_to_map(){
    drawKeypoints(map, cities_coords, map, Scalar(0,255,0), 0);
}

void Map::calc_dist_lookup(){
    // Precalculate a lookup table of distances between cities for later use.
    int num_cities = cities_coords.size();
    cities_dists.reserve(num_cities);

    for(int i = 0; i < num_cities; i++){
        vector<double> row;
        row.reserve(num_cities);

        int x_1 = cities_coords[i].pt.x;
        int y_1 = cities_coords[i].pt.y;
        for(int j = 0; j < num_cities; j++){
            int x_2 = cities_coords[j].pt.x;
            int y_2 = cities_coords[j].pt.y;
            row.push_back(sqrt(pow(x_1-x_2,2) + pow(y_1-y_2,2)));
        }

        cities_dists.push_back(row);    
    }
}
//Constructors
Map::Map(){};

Map::Map(string filename){
    map = imread(filename, CV_LOAD_IMAGE_COLOR);
    calc_cities_coords();
    calc_dist_lookup();
    add_cities_to_map();
}

//Public functions
void Map::read_map_from_file(string filename){
    map = imread(filename, CV_LOAD_IMAGE_COLOR);
}

vector<KeyPoint> Map::get_cities_coords(){
    return cities_coords;
}

vector< vector<double> > Map::get_cities_dists(){
    return cities_dists;
}
void Map::plot_map_route(vector<KeyPoint> ordered_cities, double map_scaling){
    Mat map_plot;
    map_plot = map.clone();
    for(int i = 1; i < ordered_cities.size(); i++){
        line(map_plot,ordered_cities[i-1].pt,ordered_cities[i].pt,Scalar(0,0,255),1,8,0);
    }

    if(map_scaling != 1.0){
        resize(map_plot, map_plot, Size(map_plot.cols*map_scaling, map_plot.rows*map_scaling));
    }
    
    
    imshow("Traveling Salesman Solution", map_plot);
    

    waitKey(1000/25);
}
