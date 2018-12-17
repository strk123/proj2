mkdir -p result
make
if [ $1 = "resource" ]
then
	mkdir -p result/resource
	if [ $2 = "book" ]
	then
		echo -e "Type\tName" > result/resource/book.dat
		while read Type Name || [ -n "$Type" ]
		do
		if [ $Type = "Book" ]
		then
		echo -e "$Type\t$Name" >> result/resource/book.dat
		fi
		done < resource.dat
	elif [ $2 = "e-book" ]
	then
		echo -e "Type\tName" > result/resource/e-book.dat
		while read Type Name || [ -n "$Type" ]
		do
		if [ $Type = "E-book" ]
		then
		echo -e "$Type\t$Name" >> result/resource/e-book.dat
		fi
		done < resource.dat
	elif [ $2 = "magazine" ]
	then
		echo -e "Type\tName" > result/resource/magazine.dat
		while read Type Name || [ -n "$Type" ]
		do
		if [ $Type = "Magazine" ]
		then
		echo -e "$Type\t$Name" >> result/resource/magazine.dat
		fi
		done < resource.dat
	elif [ $2 = "all" ]
	then
		echo -e "Type\tName" > result/resource/book.dat
		while read Type Name || [ -n "$Type" ]
		do
		if [ $Type = "Book" ]
		then
		echo -e "$Type\t$Name" >> result/resource/book.dat
		fi
		done < resource.dat
		echo -e "Type\tName" > result/resource/e-book.dat
		while read Type Name || [ -n "$Type" ]
		do
		if [ $Type = "E-book" ]
		then
		echo -e "$Type\t$Name" >> result/resource/e-book.dat
		fi
		done < resource.dat
		echo -e "Type\tName" > result/resource/magazine.dat
		while read Type Name || [ -n "$Type" ]
		do
		if [ $Type = "Magazine" ]
		then
		echo -e "$Type\t$Name" >> result/resource/magazine.dat
		fi
		done < resource.dat
	fi
elif [ $1 = "input" ]
then
	mkdir -p result/input
	cp input.dat input.bak
	cp space.dat space.bak
	rm input.dat space.dat
	echo -e "Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name" > input.dat
	if [ $2 = "date" ]
	then
		from_yy=`echo $3 | cut -d'/' -f1`
		from_mm=`echo $3 | cut -d'/' -f2`
		from_dd=`echo $3 | cut -d'/' -f3`
		to_yy=`echo $4 | cut -d'/' -f1`
		to_mm=`echo $4 | cut -d'/' -f2`
		to_dd=`echo $4 | cut -d'/' -f3`
		((from=$((10#${from_yy})) * 360 + $((10#${from_mm})) * 30 + $((10#${from_dd}))))
		((to=$((10#${to_yy})) * 360 + $((10#${to_mm})) * 30 + $((10#${to_dd}))))
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
			if [ $Date != "Date[yy/mm/dd]" ]
			then
				date_yy=`echo $Date | cut -d'/' -f1`
				date_mm=`echo $Date | cut -d'/' -f2`
				date_dd=`echo $Date | cut -d'/' -f3`
				((date=$((10#${date_yy})) * 360 + $((10#${date_mm})) * 30 + $((10#${date_dd}))))
				if [ $from -le $date -a $date -le $to ]
				then
					echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
				fi
			fi
		done < input.bak
		./proj
		cp output.dat result/input/date.dat
	fi
	cp input.bak input.dat
	cp space.bak space.dat
	rm output.dat input.bak space.bak

fi