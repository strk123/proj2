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
	elif [ $2 = "book" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Resource_type = "Book" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/book.dat
	elif [ $2 = "e-book" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Resource_type = "E-book" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/e-book.dat
	elif [ $2 = "magazine" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Resource_type = "Magazine" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/magazine.dat
	elif [ $2 = "undergraduate" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Member_type = "Undergraduate" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/undergraduate.dat
	elif [ $2 = "graduate" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Member_type = "Graduate" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/graduate.dat
	elif [ $2 = "faculty" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Member_type = "Faculty" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/faculty.dat
	elif [ $2 = "all" ]
	then
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Resource_type = "Book" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/book.dat
		echo -e "Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name" > input.dat
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Resource_type = "E-book" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/e-book.dat
		echo -e "Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name" > input.dat
				while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Resource_type = "Magazine" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/magazine.dat
		echo -e "Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name" > input.dat
				while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Member_type = "Undergraduate" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/undergraduate.dat
		echo -e "Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name" > input.dat
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Member_type = "Graduate" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/graduate.dat
		echo -e "Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name" > input.dat
		while read Date Resource_type Resource_name Operation Member_type Member_name
		do
		if [ $Member_type = "Faculty" ]
		then
			echo -e "$Date\t$Resource_type\t$Resource_name\t$Operation\t$Member_type\t$Member_name" >> input.dat
		fi
		done < input.bak
		./proj
		cp output.dat result/input/faculty.dat
	fi
	cp input.bak input.dat
	cp space.bak space.dat
	rm output.dat input.bak space.bak
elif [ $1 = "space" ]
then
	mkdir -p result/space
	cp input.dat input.bak
	cp space.dat space.bak
	rm input.dat space.dat
	echo -e "Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member\tTime" > space.dat
	if [ $2 = "date" ]
	then
		from_yy=`echo $3 | cut -d'/' -f1`
		from_mm=`echo $3 | cut -d'/' -f2`
		from_dd=`echo $3 | cut -d'/' -f3`
		from_hh=`echo $3 | cut -d'/' -f4`
		to_yy=`echo $4 | cut -d'/' -f1`
		to_mm=`echo $4 | cut -d'/' -f2`
		to_dd=`echo $4 | cut -d'/' -f3`
		to_hh=`echo $4 | cut -d'/' -f4`
		((from=$((10#${from_yy})) * 360 * 24 + $((10#${from_mm})) * 30 * 24 + $((10#${from_dd})) * 24 + $((10#${from_hh}))))
		((to=$((10#${to_yy})) * 360 * 24 + $((10#${to_mm})) * 30 * 24 + $((10#${to_dd})) * 24 + $((10#${to_hh}))))
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
			if [ $Date != "Date[yy/mm/dd/hh]" ]
			then
				date_yy=`echo $Date | cut -d'/' -f1`
				date_mm=`echo $Date | cut -d'/' -f2`
				date_dd=`echo $Date | cut -d'/' -f3`
				date_hh=`echo $Date | cut -d'/' -f4`
				((date=$((10#${date_yy})) * 360 * 24 + $((10#${date_mm})) * 30 * 24 + $((10#${date_dd})) * 24 + $((10#${date_hh}))))
				if [ $from -le $date -a $date -le $to ]
				then
					echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
				fi
			fi
		done < space.bak
		./proj
		cp output.dat result/space/date.dat
	elif [ $2 = "studyroom" ]
	then
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Space_type = "StudyRoom" ]
		then
			if [ $Space_number = $3 -o $3 = "all" ]
			then
				echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
			fi
		fi
		done < space.bak
		./proj
		cp output.dat result/space/studyroom.dat
	elif [ $2 = "seat" ]
	then
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Space_type = "Seat" ]
		then
			if [ $Space_number = $3 -o $3 = "all" ]
			then
				echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
			fi
		fi
		done < space.bak
		./proj
		cp output.dat result/space/seat.dat
	elif [ $2 = "undergraduate" ]
	then
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Member_type = "Undergraduate" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/undergraduate.dat
	elif [ $2 = "graduate" ]
	then
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Member_type = "Graduate" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/graduate.dat
	elif [ $2 = "faculty" ]
	then
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Member_type = "Faculty" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/faculty.dat
	elif [ $2 = "all" ]
	then
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Space_type = "StudyRoom" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/studyroom.dat
		echo -e "Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member\tTime" > space.dat
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Space_type = "Seat" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/seat.dat
		echo -e "Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member\tTime" > space.dat
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Member_type = "Undergraduate" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/undergraduate.dat
		echo -e "Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member\tTime" > space.dat
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Member_type = "Graduate" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/graduate.dat
		echo -e "Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member\tTime" > space.dat
		while read Date Space_type Space_number Operation Member_type Member_name Number_of_member Time
		do
		if [ $Member_type = "Faculty" ]
		then
			echo -e "$Date\t$Space_type\t$Space_number\t$Operation\t$Member_type\t$Member_name\t$Number_of_member\t$Time" >> space.dat
		fi
		done < space.bak
		./proj
		cp output.dat result/space/faculty.dat
	fi
	cp input.bak input.dat
	cp space.bak space.dat
	rm output.dat input.bak space.bak
elif [ $1 = "output" ]
then
	if [ $2 = "stat_table" ]
	then
		mkdir -p result/output
		./proj
		echo -e "Return_code\tNumber" > result/output/stat_table.dat
		while read Op Return_code Description
		do
			case "$Return_code" in
				-1)((N0++));;
				0) ((N1++)) ;;
				1) ((N2++));;
				2) ((N3++));;
				3) ((N4++));;
				4) ((N5++));;
				5) ((N6++));;
				6) ((N7++));;
				7) ((N8++));;
				8) ((N9++));;
				9) ((N10++));;
				10) ((N11++));;
				11) ((N12++));;
				12) ((N13++));;
				13) ((N14++));;
				14) ((N15++));;
				15) ((N16++));;
				16) ((N17++));;
			esac
		done < output.dat
		echo -e "-1\t$N0" >> result/output/stat_table.dat
		echo -e "0\t$N1" >> result/output/stat_table.dat
		echo -e "1\t$N2" >> result/output/stat_table.dat
		echo -e "2\t$N3" >> result/output/stat_table.dat
		echo -e "3\t$N4" >> result/output/stat_table.dat
		echo -e "4\t$N5" >> result/output/stat_table.dat
		echo -e "5\t$N6" >> result/output/stat_table.dat
		echo -e "6\t$N7" >> result/output/stat_table.dat
		echo -e "7\t$N8" >> result/output/stat_table.dat
		echo -e "8\t$N9" >> result/output/stat_table.dat
		echo -e "9\t$N10" >> result/output/stat_table.dat
		echo -e "10\t$N11" >> result/output/stat_table.dat
		echo -e "11\t$N12" >> result/output/stat_table.dat
		echo -e "12\t$N13" >> result/output/stat_table.dat
		echo -e "13\t$N14" >> result/output/stat_table.dat
		echo -e "14\t$N15" >> result/output/stat_table.dat
		echo -e "15\t$N16" >> result/output/stat_table.dat
		echo -e "16\t$N17" >> result/output/stat_table.dat
		rm output.dat
	fi
fi