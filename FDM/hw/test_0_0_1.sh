cat << EOF > test
#mu      a       b       M       delta_t     N
0.2     0       1       10      0.02        10 
0.3     0       1       10      0.02        10 
0.4     0       1       10      0.02        10 
0.5     0       1       10      0.02        10 
EOF

title=`head -n1 test`
#title=`cat -n test | grep "^[ ]*1" | cut -f2-`
n=`wc -l test`
i=2
while [[ $i < $n ]]
do
    #str=`cat -n test | grep "^[ ]*$i" | cut -f2-`
    str=`head -n $i test | tail -n1`
    echo ------------------------------------------
    echo Test No.`expr $i - 1`
    echo $title
    echo $str
    echo $str | ./hw_0_0_1 
    echo ------------------------------------------
    ((i++))
done

rm test
