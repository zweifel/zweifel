#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>  // for accumulate
#include<string.h>
#include<algorithm>
#include"stdio.h"
#include"Priority.h"
#include"Classic_Subpopulation.h"
using namespace std;

/*class Classic_Fitness :: public Priority
{
public:
	int objective;
	int problem_size;

	Classic_Fitness(int problem_size, int objective_index)
	{
		this->problem_size= problem_size;
		this->objective= objective_index;
	}
	
	bool compare(double* a, double* b)
	{
		return a[problem_size + objective] > b[problem_size + objective];
	}

};*/


int main()
{
  double x[6] = {1,2, 3, 5, 7, 11};
  double y[6] = {1, 1, 3, 5, 7, 11};
  double z[6] = {1,5, 3, 5, 7, 11};
  double k[6] = {1,0, 3, 5, 7, 11};
  double e[6] = {1,0.2, 3, 5, 7, 11};

  double** v= (double**)malloc(sizeof(double*)*10);

  Classic_Subpopulation* p= new Classic_Subpopulation(0, 3, 5, 1);

  //vector<double*>v;

  //v.push_back(x);
  //v.push_back(y);
  //v.push_back(z);
  

  p->testInsert(e);
  p->printSubpopulation();
  p->testInsert(k);
  p->printSubpopulation();
  p->testInsert(z);
  p->printSubpopulation();
  p->testInsert(x);
  p->printSubpopulation();
  p->testInsert(y);
  p->printSubpopulation();

/*
  printf("%f  %f  %f \n",v[0][1],v[1][1],v[2][1]);

  make_heap(v.begin(), v.end(),c::compare());
  
  printf("%f  %f  %f \n",v[0][1],v[1][1],v[2][1]);
*/
/*
  vector<int> v(&x[0], &x[5]);

 // int sum = accumulate(vector1.begin(), vector1.end(), 0);

  cout << v[0] << v[1] << v[2] << v[3] << endl;

  int a[5];
			
  memcpy(a, &v[0], 5*sizeof(double));

  printf("%d,%d,%d,%d,%d\n",a[0],a[1],a[2],a[3],a[4]);


  make_heap(v.begin(), v.end());

  printf("%d,%d,%d,%d,%d\n",v[0],v[1],v[2],v[3],v[4]);
  
  v.push_back(1);

  
  printf("%d,%d,%d,%d,%d\n",v[0],v[1],v[2],v[3],v[4]);
*/
  return 0;
}
