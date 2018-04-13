#include <enviroment.hh>

enviroment::enviroment(void)
{
	;
}

enviroment::enviroment(const int number_of_parameters, const int number_of_fireflies, const double ligth_absorption, const double beta, const std::vector<double> min, const std::vector<double> max)
{
	//Each parameter is seted
	this->number_of_parameters = number_of_parameters;
	this->number_of_fireflies = number_of_fireflies;
	this->ligth_absorption = ligth_absorption;
	//The fireflies vector beggin whit a firefly in each position.
	this->fireflies.assign(number_of_fireflies, firefly(number_of_parameters,beta,min,max));
}

void enviroment::initial_fireflies(const std::function<double(std::vector<double>,int,std::vector<double>,std::vector<double>)> fitness)
{
	for(int i=0;i<this->number_of_fireflies;i++)
	{
		this->fireflies[i].generate_solution(fitness);
	}
}

void enviroment::move_fireflies(const double alpha, const double betta_0, const double step_size, const std::function<double(std::vector<double>,int,std::vector<double>,std::vector<double>)> fitness)
{
	double distance;
	//Each firefly is compared with the rest ones and is moved to the brigher ones
	for(int i=0;i<this->number_of_fireflies;i++)
	{
		for(int j=0;j<this->number_of_fireflies;j++)
		{
			distance = this->distance(this->fireflies[i].get_solution(),this->fireflies[j].get_solution());
			//TODO : Compare performance bewteen the ifs
			//if(i!=j && (this->fireflies[j].get_light_intensity()/pow(distance,2)) > this->fireflies[i].get_light_intensity())
			//Si no se usa la distancia queda así (acorde al código de matlab del creador)
			if(i!=j && this->fireflies[j].get_light_intensity() > this->fireflies[i].get_light_intensity())
			//Esta sería utilizando el concepto del atractivo
			//if(i!=j && (this->fireflies[j].get_light_intensity()*exp(-this->ligth_absorption*pow(distance,2.0))) > this->fireflies[i].get_light_intensity())
			{
				this->fireflies[i].move(this->fireflies[j].get_solution(),alpha,betta_0,this->ligth_absorption,distance,step_size);
				//this->fireflies[i].update_light_intensity(fitness);				
			}
		}
	}
}

void enviroment::update_fireflies_light(const std::function<double(std::vector<double>,int,std::vector<double>,std::vector<double>)> fitness)
{
	for(int i=0;i<this->number_of_fireflies;i++)
	{
		this->fireflies[i].update_light_intensity(fitness);
	}
}

double enviroment::distance(const std::vector<double> firefly_i, const std::vector<double> firefly_j) const
{
	double distance=0.0;
	for(int i=0;i<this->number_of_fireflies;i++)
	{
		distance = distance + pow(firefly_i[i]-firefly_j[i],2);
	}
	return sqrt(distance);
}

void enviroment::rank_fireflies(void)
{
	std::sort(this->fireflies.begin(), this->fireflies.begin() + this->number_of_fireflies,[](firefly const &f1, firefly const &f2) -> bool{return f1.get_light_intensity() < f2.get_light_intensity();});
}

double enviroment::get_brighter_firefly(void)
{
	return this->fireflies[0].get_light_intensity();
}

void enviroment::update_solutions(void)
{
	for(int i=0;i<this->number_of_fireflies;i++)
	{
		this->fireflies[i].update_solution();
	}
}

void enviroment::post_process(void)
{
	double mean=0;
	for(int i=0;i<this->number_of_fireflies;i++)
	{
		mean = mean + this->fireflies[i].get_light_intensity();
	}
	mean = mean/this->number_of_fireflies;
	std::cout << "Min/Max/Avg Fitness " << "[" << this->fireflies[0].get_light_intensity() << "," << this->fireflies[this->number_of_fireflies-1].get_light_intensity() << "," << mean <<"]" << std::endl;
}

std::vector<double> enviroment::get_brighter_firefly_solution(void)
{
	return this->fireflies[0].get_solution();
}

enviroment::~enviroment(void)
{
	;
}