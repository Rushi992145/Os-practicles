echo "Enter a"
read a

echo "Enter b"
read b

echo "Enter c"
read c

if [ $a -gt $b ] && [ $a -gt $c ]
then
echo "$a is greater than $b and $c"
elif [ $b -gt $a ] && [ $b -gt $c ]
then 
echo "$b is greater than $a and $c"
else 
echo "$c is greater than $a and $b"
fi

echo "End"