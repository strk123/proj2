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
fi