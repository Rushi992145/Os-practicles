echo "cheack wheter the number is prime or not"
read -p'Enter the number: ' num
i=2 
flag = 0

while [ $i -le $((num/2))]
do
if[$((num%i)) -eq 0]; then
    flag = 1
    break
fi

i = $(($i+1))
done

if[ $flag -eq 1]; then 
    echo "Number is Not prime"
else 
    echo "Number is prime"
fi