#include <vector>
#include <functional>
#include <random>
#include <math.h>
#include <iostream>

class firefly{

private:
	//Parameter for the levy flight.
	double betta;
	//Parameter for the levy flight.
	double sigma_u;
	//Parameter for the levy flight.
	double sigma_v;
	//Random number generator for the distribution u in the levy fligh.
	std::uniform_real_distribution<double> distribution_u;
	//Random number generator for the distribution v in the levy fligh.
	std::uniform_real_distribution<double> distribution_v;
	//Random number generator for the direction in the levy fligh.
	std::uniform_real_distribution<double> direction;
	//Used for the sign in the movement of the firefly
	std::uniform_real_distribution<double> sign_selector;
	//Number of parameters in the problem
	int number_of_parameters;
	//A vector thar represent the solution of the problem
	std::vector<double> solution;
	//Light intensity (e.g fitness) of the firefly. Used to compare with others and move towards the best ones
	double ligth_intensity;
	//Vector that contains uniform distributions for each parameter in the problem
	std::vector<std::uniform_real_distribution<double> > parameters_distributions;

public:
	//Empy constructor
	firefly(void);
	//Constructor of the class
	//	int number of parameter = number of parameters in the problem
	//	double betta = used in the levy flight
	//	vector lower_bounds = lower bounds of each parameter
	//	vector upped_bounds = upper bounds of each parameter
	firefly(const int number_of_parameters, const double betta, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds);
	//Generate a solution for the firefly
	void generate_solution(const std::function<double(std::vector<double>,int)> fitness);
	//Perfom a Levy flight
	//	double step_size = Actual step size of the Levy flight
	double levy_flight(const double &step_size);
	//Get the light intensity of the firefly
	double get_light_intensity(void) const; 
	//Move the firefly towards a better one
	//	vector brighter_firefly = brighter (best) firefly to do the movement
	//	double alpha = randomazition parameter. Muste be a value bewteen 0 and 1 (highly random)
	//	double betta_0 = atractiveness at r=0
	//	double light_absorption = light absorption factor. Must be a value bewteen 0 and 1
	//	double distance = distance between the current (this) firefly and the one towards the movement
	//	double step_size = Used in the levy flight
	//	vector lower_bounds = lower bounds of each parameter
	//	vector upped_bounds = upper bounds of each parameter
	void move(const std::vector<double> brighter_firefly, const double alpha, const double betta_0, const double light_absorption, const double distance, const double step_size, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds);
	//Update the light intensity of the firefly
	void update_light_intensity(const std::function<double(std::vector<double>,int)> fitness);
	//Get a sign (e.g -1 or 1) with 50% chance each
	double sign(void);
	//Get the solution of the firefly
	std::vector<double> get_solution(void) const;
	//Destructor
	~firefly(void);
};