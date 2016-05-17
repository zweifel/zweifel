// -*- c++ -*-
//
//  File:         random.cpp
//
//  Description:  C++ implementation of the random number generator class.
//                eCGA version 1.0 implemented Prime Modulus Multiplicative 
//                Linear Congruential Genertator (PMMLCG), based on the paper 
//                by Park and Miller published in the Communications of the
//                ACM, October 1988.
//                ECGA version 1.1 uses Mersenne Twister by M. Matsumoto and 
//                T. Nishimura. See 
//                http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html 
//                for more information on Mersenne Twister                               *
//
//  Authors:       Fernando Lobo, Kumara Sastry
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 and changed the
//  pseudo-random number generator to Mersenne twister by Kumara Sastry

//
//  Date:        March/2006

#include <iostream>
#include <math.h>
#include <assert.h>

#include "random.hpp"

// Create a new seed for the random number generator using the time of the day.
unsigned long randomG::makeSeed()
{
  time_t tp;
  struct tm *temp;
  unsigned int temp2, temp3;
  static unsigned int temp4 = 0xe0e1; 
  
  time(&tp);
  temp = localtime(&tp);
  
  temp2 = (temp->tm_sec<<26)+(temp->tm_min<<20)+(temp->tm_hour<<15)+
    (temp->tm_mday<<10)+(temp->tm_mon<<6);
  temp3 = (temp->tm_year<<13)+(temp->tm_wday<<10)+(temp->tm_yday<<1)+
    temp->tm_isdst;
  temp2 ^= clock()^temp3;
  
  temp4 = (temp4*0xeeee)%0xffff;
  temp2 ^= temp4<<16;
  temp4 = (temp4*0xaeee)%0xffff;
  temp2 ^= temp4;
  temp2 &= 0x7fffffff;
  return (unsigned long)temp2;
}

/* initializes mt[N] with a seed */
void randomG::init_Mersenne()
{
  mt[0] = Seed & 0xffffffffUL;
  for (mti=1; mti<Nmt; mti++) {
    mt[mti] = 
      (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
    /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
    /* In the previous versions, MSBs of the seed affect   */
    /* only MSBs of the array mt[].                        */
    /* 2002/01/09 modified by Makoto Matsumoto             */
    mt[mti] &= 0xffffffffUL;
    /* for >32 bit machines */
  }
}

//
// if a seed is not given, ask for one.
// seed must be an integer between 1 and m-1
//
void randomG::randomize( int seed )
{
  //  int my_rng_type = SPRNG_LCG;
  if( seed == UNSET ) {
    Seed = makeSeed();
  }
  else 
    Seed = (unsigned long) seed;
#ifndef	NOPRINTF
  std::cout << "Seed: = " << Seed << std::endl;
#endif
  assert( Seed > 0 );
  //  Stream = init_sprng(my_rng_type, 0, 1, Seed, SPRNG_DEFAULT);
  init_Mersenne();
}

//
// seed must be a real number between 0 and 1
//
void randomG::randomize( double seed )
{
  int M1 = 12345678;
  //  int my_rng_type = SPRNG_LCG;
  int Seed = (unsigned long)( 1 + seed * (M1-2) );
  assert( Seed>0 && Seed<M1 );
  //Stream = init_sprng(my_rng_type, 0, 1, Seed, SPRNG_DEFAULT);
  init_Mersenne();
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long randomG::genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= Nmt) { /* generate N words at one time */
        int kk;

        if (mti == Nmt+1)  { /* if init_genrand() has not been called, */
          Seed = 5489UL; 
          init_Mersenne(); /* a default initial seed is used */
        }
        for (kk=0;kk<Nmt-Mmt;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+Mmt] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<Nmt-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(Mmt-Nmt)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[Nmt-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[Nmt-1] = mt[Mmt-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long randomG::genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double randomG::genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double randomG::genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double randomG::genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double randomG::genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */


//
// generate a random number distributed uniformly in 0..1
//
double randomG::uniform01()
{
  return(genrand_res53());
}

double randomG::uniform( double a, double b )
{
  assert( b > a );
  return (b-a) * uniform01() + a;
}

int randomG::uniform( int a, int b )
{
	if(a==b)
	{
		return a;
	}

  assert( b > a );
  int i = int( (b-a+1) * uniform01() + a );
  if( i>b ) i=b;
  return i;
}

//
// generate a random number with an exponential distribution with mean 'mu'
// note: log(x) gives the natural logarithm of x.
//
double randomG::exponential( double mu )
{
  double U = uniform01();
  return -mu*log(U);
}

//
// generate a Bernoulli trial with probability of success 'p'
//
bool randomG::bernoulli( double p )
{
  return ( uniform01() < p );
}
  
//
// generate a sample from a Geometric random variable with parameter 'p'.
// returns how many successes not including the first failure. 
// 'p' is the probability of failure.
//
long randomG::geometric( double p )
{
  double U = uniform01();
  return int( log(U)/log(1-p) );
}

//
// generate a sample from the standard normal distribution (mean=0, var=1).
// see book "Simulation Modeling and Analysis" by Law & Kelton, pag. 490-491.
//
double randomG::normal01()
{
  double U1, U2, V1, V2, W, Y, X1, X2;

  do {
    U1 = uniform01(); 
    U2 = uniform01();
    V1 = 2*U1 - 1;
    V2 = 2*U2 - 1;
    W  = V1*V1 + V2*V2;
  } while( W > 1 );
  
  Y = sqrt( (-2*log(W)) / W );
  X1 = V1 * Y;
  X2 = V2 * Y;

  return X1;
}

//
// generate a sample from a normal distribution with 
// mean 'mean' and variance 'variance'.
//
double randomG::normal( double mean, double variance )
{
  double X = normal01();
  double stddev = sqrt( variance );

  return mean + stddev * X;
}
