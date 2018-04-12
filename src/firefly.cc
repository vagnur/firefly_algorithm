#include <firefly.hh>

firefly::firefly(void)
{
	;
}

firefly::firefly(const int number_of_parameters, const double betta, const std::vector<double> min, const std::vector<double> max)
{
	//Each attribute of the class is initialized and the memory is reserved for each vector.
	this->betta = betta;
	//Sigma u is calculated (see levy flight method for more info)
	this->sigma_u = pow((tgamma(1+betta)*sin(M_PI*betta/2))/(tgamma((1+betta)/2)*betta*pow(2,(betta-1)/2)),1/betta);
	this->sigma_v = 1;
	std::uniform_real_distribution<double> distribution_u(0.0,this->sigma_u);
	this->distribution_u = distribution_u;
	std::uniform_real_distribution<double> distribution_v(0.0,this->sigma_v);
	this->distribution_v = distribution_v;
	std::uniform_real_distribution<double> direction(0.0,1.0);
	this->direction = direction;
	std::uniform_real_distribution<double> sign(0.0,1.0);
	this->sign_selector = sign;
	this->number_of_parameters = number_of_parameters;
	this->solution.resize(number_of_parameters);
	this->new_solution.resize(number_of_parameters);
	std::uniform_real_distribution<double> parameter_selector(0.0, 1.0);
	this->parameter_selector = parameter_selector;
	this->min = min;
	this->max = max;
}

void firefly::generate_solution(const std::function<double(std::vector<double>,int,std::vector<double>,std::vector<double>)> fitness)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
	for(int i=0;i<this->number_of_parameters;i++)
	{
		//For each parameter, a random value is obtained and setted in the i position of the solution vector
		this->solution[i] = this->parameter_selector(generator);;
	}
	//Calcuate the light intesity (e.g fitness) for the given solution
	this->ligth_intensity = fitness(this->solution,this->number_of_parameters,this->min,this->max);
}

double firefly::levy_flight(const double &step_size)
{
	/*
		This levy flights implementation correspond to the Mantenga's algorithm for the step lenght.
		u and v are the parameters for the equation that describe the step lenght s
			s = u/(|v|^(1/Betta))
		where u and v are drawn from normal distributions, that means
			u ~ N(0,sigma_u^2) and v ~ N(0,sigma_v^2)
		whit sigma_v = 1 and sigma_u given by the next equation
			sigma_u = {Gamma(1+Betta)*Sin(Pi*Betta/2)/Gamma[(1+Betta)/2]*Betta*2^(Betta-1)/2}^1/Betta
		Where Gamma is the gamma function and Betta is a parameter of the algorithm 
	*/

	//Get a random number for u and v. Then calculate the step lenght s.
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
	double u = this->distribution_u(generator); 
	double v = this->distribution_v(generator);
	double s = u/pow(fabs(v),1/this->betta); 
	//Return the step lenght (s).
	return step_size*s;
}

void firefly::move(const std::vector<double> brighter_firefly, const double alpha, const double betta_0, const double light_absorption, const double distance, const double step_size)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
    double levy_flight_perform_step, direction, attraction;
	for(int i=0;i<this->number_of_parameters;i++)
	{
		//Levy flight perfom
		levy_flight_perform_step = this->levy_flight(step_size);
		direction = this->direction(generator);
		//Attractiveness of the firefly
		attraction = betta_0 * exp(-1*light_absorption*pow(distance,2));
		this->new_solution[i] = ((this->solution[i]*(1-attraction)) + (brighter_firefly[i]*attraction) + (alpha * this->sign() )) + levy_flight_perform_step * direction;
		//Aplication of the bounds if needed
		if(this->new_solution[i] > 1.0)
		{
			this->new_solution[i] = 1.0;
		}
		if(this->new_solution[i] < 0.0)
		{
			this->new_solution[i] = 0.0;
		}
	}
}

void firefly::update_light_intensity(const std::function<double(std::vector<double>,int,std::vector<double>,std::vector<double>)> fitness)
{
	this->ligth_intensity = fitness(this->solution,this->number_of_parameters,this->min,this->max);
}

void firefly::update_solution(void)
{
	for(int i=0;i<this->number_of_parameters;i++)
	{
		this->solution[i] = this->new_solution[i];
	}
}


double firefly::sign(void)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
    double value = this->sign_selector(generator);
    if(value > 0.5)
    {
    	return 1.0;
    }
    else
    {
    	return -1.0;
    }
}

double firefly::get_light_intensity(void) const
{
	return this->ligth_intensity;
}

std::vector<double> firefly::get_solution(void) const
{
	return this->solution;
}

firefly::~firefly(void)
{
	;
}