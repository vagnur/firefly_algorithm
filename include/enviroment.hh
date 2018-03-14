#include <vector>
#include <functional>
#include <firefly.hh>
#include <math.h>
#include <algorithm>

class enviroment{

private:
	//Number of parameters in the problem
	int number_of_parameters;
	//Number of fireflies to use in the algorithm
	int number_of_fireflies;
	//Vector that contains the fireflies
	std::vector<firefly> fireflies;
	//Light absorption factor. Must be a value bewteen 0 and 1
	double ligth_absorption;

public:
	//Empy constructor
	enviroment(void);
	//Constructor of the enviroment class
	//	int number_of_parameters = number of parameters in the problem
	//	int number_of_fireflies = number of fireflies to ue in the algorithm
	//	double ligth_absorption = light abosrption in the medium. It affects the movement of the fireflies.
	//	double beta = used in the Levy flight
	//	vector lower_bounds = lower bounds of each parameter
	//	vector upped_bounds = upper bounds of each parameter	
	enviroment(const int number_of_parameters, const int number_of_fireflies, const double ligth_absorption, const double beta, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds);
	//Initialize each firefly (create a initial solution)
	//	function fitness = function to eavaluate each firefly and obtain the light intensity (e.g fitness) of each fifrefly
	void initial_fireflies(const std::function<double(std::vector<double>,int)> fitness);
	//Move the fireflies towards the brighter ones
	//	double alpha = randomazition parameter. Muste be a value bewteen 0 and 1 (highly random)
	//	double betta_0 = attractiveness at r = 0
	//	double step_size = the actual size of the levy fligt
	//	vector lower_bounds = lower bounds of each parameter
	//	vector upped_bounds = upper bounds of each parameter
	void move_fireflies(const double alpha, const double betta_0, const double step_size, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds, const std::function<double(std::vector<double>,int)> fitness);
	//Update the fireflies light after the movement
	void update_fireflies_light(const std::function<double(std::vector<double>,int)> fitness);
	//Order the fireflies according to their light intensity
	void rank_fireflies(void);
	//Calcuate the distance bewteen two fireflies
	//	vector firefly_i = one of the fireflies to calculate the distance
	//	vector firefly_j = one of the fireflies to calculate the distance
	double distance(const std::vector<double> firefly_i, const std::vector<double> firefly_j) const;
	//Get the brighter (e.g best) firefly
	double get_brighter_firefly(void);
	//Get the solution of the brighter (e.g best) firefly
	std::vector<double> get_brighter_firefly_solution(void);
	//Post process that show info about the fireflies
	void post_process(void);
	//Destructor
	~enviroment(void);
};