wget -O forparsing.html $1 2>/dev/null
if [ $1 ]
then
	if [[ $1 =~ binarypuzzle.com ]]
	then
		if [[ $1 =~ binarypuzzle.com$ ]]
		then
			iterations=`grep "Size:" forparsing.html | awk '{print substr($3, 0, match($3, /x/)-1)}'`
		else
			iterations=`grep "<title>" forparsing.html | awk '{print substr($1, match($1, />/)+1, match($1, /x/) - match($1, />/) -1 )}'`
		fi
		tail -n +51 forparsing.html | grep "\s</p>" | awk -v var=0 -v iter=$iterations '$1 !~ /<\/p>/ {printf $1; printf " ";var=var+1} $1 ~ /<\/p>/ {printf "- " ; var=var+1} (var==iter) {print ""; var=0}' > input
    a.out < input > myResults 
		grep -E "oplossing\[([0-9]|[0-9][0-9])\]" forparsing.html | awk -v sum=0 -v total=$iterations '{printf substr($3, 2, length($3)-4)" "; sum+=1} (sum==total){print ""; sum = 0}' > results
	else
		echo "Link not supported"
    exit
	fi
else
	echo "No link provided"
  exit
fi
diff results myResults
rm forparsing.html #results myResults
for i in `ls tests/*in`
do
	diff $i input 1>/dev/null
	if [ $? -eq 0 ]
	then
		echo "Puzzle is duplicate of test file"
		exit
	fi
done
tests=`ls tests/ | wc -l`
tests=$((tests/3))
tests=$((tests+1))
mv results tests/t$tests.out
mv input tests/t$tests.in
mv myResults tests/t$tests.myout
