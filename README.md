# Firefly Algorithm

C++ implementation of the firefly algorithm metaheuristic for optmization problems.

## Installation

In order to use the firefly algorithm, you need to use the makefile of the repository:

```
~@ make 
```

## Usage

First, you need to declare the fitness function. In the code we have an example of a fitness function. The algorithm searchs in a [0,1] space, so you need to adjust the value of the parameters in the fitness function, see the example in [fireflyalgorithm.cc](../master/src/fireflyalgorithm.cc) file for details.

Then, you need a file that contains the minimun and maximun value of each parameter _i_, like this:

```
0 1 2 3 4
4 5 6 7 8
```

In this case the parameters min and max, when _i=3_ for example, are 2 and 6 respectively.

To execute the program you need to execute:


```
~@ ./fa -p -f -g -b -a -t -l -s
```

Where:

* p -> The number of parameters in the problem
* f -> The number of fireflies
* g -> Maximun number of generations
* b -> Betta parameter for the levy flight
* a -> Alpha parameter
* t -> Betta at moment 0
* l -> Light absoprtion
* s -> Stop criterion

## Algorithm

For more information about cuckoo search see _Yang, X. S. (2010). Firefly algorithm, stochastic test functions and design optimisation. International Journal of Bio-Inspired Computation, 2(2), 78-84._

For more information about Levy Flights see chapter 2 of _Yang, X. S. (2010). Nature-inspired metaheuristic algorithms. Luniver press._

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](../master/LICENSE) file for details.
