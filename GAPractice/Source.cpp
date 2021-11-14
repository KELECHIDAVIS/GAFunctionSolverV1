#include <iostream>
#include <vector>
#include <algorithm>

float problem(float x, float y) // the porblem to solve
{// i want the product to be equal to 32 so the closer it is to zero the better ; ideally the first value can be 2 and the second value can be 5
	return pow(x, x) *y -128;


}
float fitness(float val);
float sigmoid(float fit); 
float randRange() { // btween .9 and 1.1
	
	return (0.9 + ((rand() % 100) /100.0f)*0.2); 
}

struct Chrom
{
	float x, y, fitness;
	Chrom()
	{//rand numbers up to 1000
		
		x = rand() % 1000;
		y = rand() % 1000;

	}
	Chrom(float x, float y)
	{
		this->x = x;
		this->y = y;

	}

	float getFit()
	{
		return this->fitness;
	}
	void setFit(float fit)
	{
		this->fitness = fit;
	}

	bool operator < (const Chrom chrom) const // makes the chrom objects comparable to others 
	{
		return (fitness > chrom.fitness);   // this will make it sort in descending order
	}

};

void populate(std::vector<Chrom>& solutions, int size); 
std::vector<Chrom> newGen(std::vector<Chrom> &top);

//code


int main()
{
	//determine what the problem is 
	// then solve 
	
	bool running = true;  // when the answer is found this will turn false then end the loop 
	srand(time(NULL)); // set the rand seed 
	std::vector<Chrom> solutions; 
	populate(solutions, 10000);
	int gen = 0; 
	while (running)
	{
		gen++; 
		std::cout <<"GEN "<< gen << std::endl;
		std::vector<Chrom> topSolutions;

		for (int i = 0; i < 5000; i++) // top 5000 
		{
			topSolutions.push_back(solutions[i]);
		}


		solutions = newGen(topSolutions);
		
		
		if (solutions[0].fitness>=999999)
		{
			//found solution or got close 
			std::cout << "Winner: " << solutions[0].x << ", " << solutions[0].y << " ; Percent Sure: " << sigmoid( solutions[0].getFit())<<"%" <<std::endl;
			std::cout <<"Gen: "<< gen << std::endl; 
			
			running = false; 

		}
	}
	
	 
	
		//std::vector<Chrom> topSolutions;

		//for (int i = 0; i < 5000; i++) // top 5000 
		//{
		//	topSolutions.push_back(solutions[i]);
		//}


		//solutions = newGen(topSolutions);

	
	
	



	return 0;
}


void populate(std::vector<Chrom>& solutions, int size)
{
	for (int i = 0; i < size; i++) // starts generation of 5000  randomly 
	{
		solutions.push_back(Chrom());
		solutions[i].setFit(fitness(problem(solutions[i].x, solutions[i].y)));



	}
	//sorts it too 
	std::sort(solutions.begin(), solutions.end()); 
	
	std::cout << "Best Fit of Gen : " << solutions[0].getFit() <<"(" << solutions[0].x <<", "<< solutions[0].y<<")"<< std::endl;
	
}
std::vector<Chrom> newGen(std::vector<Chrom> &top)
{
	std::vector<Chrom> temp;

	// add the first 5000 best ; 3200 through crossover; 1400 through mutation ; 400 rand; 
	//then sort by fitness
	for (int i = 0;i<3000 ;i++ )
	{
		temp.push_back(top[i]); 
	}
	// crossover ;  takes a random x and a random y from some of the best 
	for (int i = 0; i < 4200; i++) // should maybe mutate all the children slightly or make the size of mutated children bigger
	{
		int randX = (int)(rand() % temp.size());
		int randY = (int)(rand() % temp.size());
		// make a new chrom from two random parents  ; then mutates it slightly 
		Chrom child(temp[randX].x, temp[randY].y);
		child.setFit(fitness(problem(child.x, child.y))); 
		temp.push_back(child);

	}
	for (int i = 0; i <2400 ; i++) // should maybe mutate all the children slightly or make the size of mutated children bigger
	{
		int randX = (int)(rand() % temp.size());
		int randY = (int)(rand() % temp.size());
		// make a new chrom from two random parents  ; then mutates it slightly 
		Chrom child(temp[randX].x, temp[randY].y);
		child.x = child.x * randRange();  // mutates it by a uniform distribution between .9 and 1.1  (.2 )
		child.y = child.y * randRange();
		child.setFit(fitness(problem(child.x, child.y))); 
		temp.push_back(child);
	}
	for (int i = 0; i < 400; i++)
	{
		Chrom randChrom; 
		randChrom.setFit(fitness(problem(randChrom.x, randChrom.y))); 
		temp.push_back(randChrom); // a random chrom  for variety 

	}
	//sort 
	std::sort(temp.begin(), temp.end()); 

	std::cout << "Percent Sure :  1st: " << sigmoid(temp[0].getFit()) << "%  (" << temp[0].x << ", " << temp[0].y << ")" << " |2nd: " << sigmoid(temp[1].getFit()) << "%  (" << temp[1].x << ", " << temp[1].y << ")" << " |3rd: " << sigmoid(temp[2].getFit()) << "%  (" << temp[2].x << ", " << temp[2].y << ")" << std::endl;
	return temp; 

}



float fitness(float val) // the closer val is to 0 the better because its closer to wat i want
{
	// but if it is zero that means that it was solved so i want to award a lot of points
	if (val == 0)
	{
		return 9999999;
	}
	else
	{
		return abs(1.f / val); // this is good because the closer that val is to 0 the bigger the number
	}
}


float sigmoid(float fit) // the fit is going to act like the x in the sigmoid function  (regular sig func just the x is added to and divided by 1000 to horizontally stretch and the whole thing is multiplied by  100  to give better, more accurate percentages)
{
	float x = ((-fit + 3000))/1000.f; // for the transformation 

	return 100.f/(1.f+exp(x)); 


}