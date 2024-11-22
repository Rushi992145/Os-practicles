echo "Enter the choice 1.Addition 2.Substraction 3.Multiplication 4.Division 5.Modulus"
read n

echo "Enter 2 Numbers"
read a
read b

case $n in
1) echo "Addition is $(($a+$b))"
;;
2) echo "Substraction is $(($a-$b))"
;;
3) echo "Multiplication is $(($a*$b))"
;;
4) echo "Division is $(($a/$b))"
;;
5) echo "Modulus is $(($a%$b))"
;;
*) echo "Invalid input"
;;
esac