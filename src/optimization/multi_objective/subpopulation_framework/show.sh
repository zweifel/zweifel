#!/bin/bash

R -f plot.r

xv plot.png

cp solutions old_solutions
rm solutions