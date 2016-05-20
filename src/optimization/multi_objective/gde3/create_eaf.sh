
rm eaf_file

for i in `seq 1 30`
do
	echo "trial" $i
	rm solutions
	./o > /dev/null
	R -f process.r
	cat processed_solutions >> eaf_file
	echo "" >> eaf_file
done
