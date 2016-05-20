#!/bin/bash
#NOTE: the Makefile should compile with "-c"

install_destination='../../lib/'
libname="libzoptimization.a"
object_files="differential_evolution/Differential_Evolution.o \
	Generic_Problem.o \
	Problem_Test.o \
	multi_objective/gde3/GDE3.o \
	multi_objective/subpopulation_framework/Subpopulation_Framework.o \
	multi_objective/subpopulation_framework/Novelty_Subpopulation.o \
	multi_objective/subpopulation_framework/Classic_Subpopulation.o \
	multi_objective/subpopulation_framework/Subpopulation.o"
#object_files="differential_evolution/Differential_Evolution.o goldberg_ga_theory/Goldberg_GA.o goldberg_ga_theory/random.o"

tmp_destination="lib/"


##################
function if_error
##################
{
if [[ $? -ne 0 ]]; then # check return code passed to function
echo "$1" 
exit $?
fi
}

echo "Compiling..."
make compile 2>/dev/null 1>/dev/null
if_error "ERROR: Source Code does not compile!"

mkdir $tmp_destination

echo "Creating Libraries:"

echo "Building lib..."
ar rcs $tmp_destination$libname $object_files

mv $tmp_destination$libname $install_destination
rmdir $tmp_destination
rm *.o



