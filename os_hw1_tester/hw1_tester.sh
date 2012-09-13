#/bin/sh
if [ $# -ne 1 ]
then
	echo "How to Use) \$sh hw1_tester.sh [path/of/binary/to/test]"
	exit 1;
fi

EXEC=$1
INPUTS=$(ls *\.in)
TARGETDIR=$(dirname $1)
TOTAL=0
ANSWER=0
rm -f $TARGETDIR/*.output $TARGETDIR/Score.txt
echo "Tesing: $1"
for input in $INPUTS
do
	trimmed=$(echo $input | sed 's/\./-/' | sed 's/-in//')
	echo -n "Running test: $trimmed ... "
	$($1 < $input > $TARGETDIR/$trimmed.output) 
	diff -Bbi $trimmed.out $TARGETDIR/$trimmed.output > $TARGETDIR/$trimmed.result
	if [ $? -eq 0 ]
	then
		echo "pass"
		ANSWER=`expr $ANSWER + 1`
	else
		echo "fail"
	fi
	TOTAL=`expr $TOTAL + 1`
done
echo "Result: $ANSWER / $TOTAL"
echo "$ANSWER" > $TARGETDIR/Score.txt


