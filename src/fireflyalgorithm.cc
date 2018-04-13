#include <iostream>
#include <fstream>
#include <unistd.h>
#include <enviroment.hh>

double fitness(std::vector<double> solution,int number_of_parameters,std::vector<double> min,std::vector<double> max);

int main(int argc, char** argv)
{
	//Parameters for the algorithm
	//	char c = Used for the getopt options
	//	int number_of_parameters = number of parameters in the problem
	//	int number_of_fireflies = number of fireflies to use in the algorithm
	//	int max_generations = maximum number of iterations to use in the algorithm
	//	int output = used to give feedback to the user (indicates the frecuency)
	//	double betta = used in the levy flight
	//	double alpha = randomazition parameter. Must be a value bewteen 0 and 1 (highly random)
	//	double betta_0 = attractiveness at r=0
	//	double light_absorption = light absorption factor. Must be a value bewteen 0 and 1
	//	double stop_criterion = minium value for the fitness. If the criterion is satisfied, the algorithm stops
	char c;
	int number_of_parameters=0,number_of_fireflies=0,max_generations=0,t=0,output=10;
	double betta=0.0,alpha=0.0,betta_0=0.0,light_absorption=0.0,stop_criterion=0.0;
	extern char *optarg;
	while((c=getopt(argc,argv,"p:f:g:b:a:t:l:o:s:"))!=-1)
	{
		switch (c)
		{
			case 'p':
				number_of_parameters = std::stoi(optarg);
				break;
			case 'f':
				number_of_fireflies = std::stoi(optarg);
				break;
			case 'g':
				max_generations = std::stoi(optarg);
				break;
			case 'b':
				betta = std::stod(optarg);
				break;
			case 'a':
				alpha = std::stod(optarg);
				break;
			case 't':
				betta_0 = std::stod(optarg);
				break;
			case 'l':
				light_absorption = std::stod(optarg);
				break;
			case 's':
				stop_criterion = std::stod(optarg);
				break;
		}
	}
	//Parameters verification
	if(number_of_parameters==0)
	{
		std::cout << "Mandatory parameter -p (number of parameters) needed" << std::endl;
		return -1;
	}
	if(number_of_fireflies==0)
	{
		std::cout << "Mandatory parameter -f (number of fireflies) needed" << std::endl;
		return -1;
	}
	if(max_generations==0)
	{
		std::cout << "Mandatory parameter -g (max number of iterations) needed" << std::endl;
		return -1;
	}
	if(betta==0)
	{
		std::cout << "Mandatory parameter -b (betta) needed" << std::endl;
		return -1;
	}
	if(alpha==0)
	{
		std::cout << "Mandatory parameter -a (alpha) needed" << std::endl;
		return -1;
	}
	if(betta_0==0)
	{
		std::cout << "Mandatory parameter -t (betta_0)[Atractiveness at r=0] needed" << std::endl;
		return -1;
	}
	if(light_absorption==0)
	{
		std::cout << "Mandatory parameter -l (light absorption)[gamma] needed" << std::endl;
		return -1;
	}
	if(stop_criterion==0.0)
	{
		std::cout << "Mandatory parameter -s (stop criterion) needed" << std::endl;
		return -1;
	}

	//Min and max for each parameter
	std::vector<double> min(number_of_parameters);
	std::vector<double> max(number_of_parameters);

	//File read
	std::ifstream input;
	input.open("input.data",std::ifstream::in);
	for(int i=0;i<number_of_parameters;i++)
	{
		input >> min[i];
	}
	for(int i=0;i<number_of_parameters;i++)
	{
		input >> max[i];
	}
	input.close();

	//Initialization of the enviroment
	enviroment env(number_of_parameters,number_of_fireflies,light_absorption,betta,min,max);

	//Generation of the initial fireflies
	env.initial_fireflies(fitness);

	while(t < max_generations)
	{
		//Move the fireflies towards the brighter ones
		env.move_fireflies(alpha,betta_0,0.01,fitness);
		//Update the fireflies light intensity
		env.update_solutions();
		env.update_fireflies_light(fitness);
		//Order the fireflies according to the light intensity
		env.rank_fireflies();
		t++;
		//Feedback
		if(t%output==0)
		{
			env.post_process();
		}
		//If the best firefly met the stop criterion, then the algorithm stops
		if(env.get_brighter_firefly() < stop_criterion)
		{
			break;
		}
	}

	std::vector<double> best_firefly(number_of_parameters);
	best_firefly = env.get_brighter_firefly_solution();
	std::cout << "Best firefly at generation: " << t  << std::endl;
	for(int i=0;i<number_of_parameters;i++)
	{
		std::cout << (best_firefly[i]*(max[i]-min[i]))+min[i] << " ";
	}
	std::cout << std::endl;

	return 0; 
}

//Example of fitness
//In this case, the algorithm needs to guess the sequence [0,1,2,3,4]
double fitness(std::vector<double> solution, int number_of_parameters, std::vector<double> min, std::vector<double> max)
{
	double fitness=0,value,unormal_value;
	//In this case wee use the Mean squared error
	for(unsigned int i=0;i<solution.size();i++)
	{
		//See that, since the algorithm searchs in a [0,1] space,
		//is necesary to adjust the values in the search space
		unormal_value = (solution[i]*(max[i]-min[i]))+min[i];	
		value = i - unormal_value;
		fitness = fitness + pow(value,2);
	}
	return fitness/number_of_parameters;
}