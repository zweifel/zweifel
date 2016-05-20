#!/bin/bash

R -f plot.r

feh plot.png

cp solutions old_solutions
rm solutions
