
rm eaf_file*

for i in `seq 1 30`
do
	echo "trial" $i
	rm *solutions
	./o > /dev/null
	
	for j in `ls *solutions`
	do
		echo $j
		number=`echo $j|cut -d '_' -f 1`
		cp $j solutions
		R -f process.r
		cat processed_solutions >> eaf_file_$number
		echo "" >> eaf_file_$number
		#echo eaf_file_$number
	done
	#R -f process.r
	#cat processed_solutions >> eaf_file
	#echo "" >> eaf_file
done
