while true
do
  ./gen >test.in
  ./job <test.in >output.txt || break
  ./job_2 <test.in >answer.txt || break
  
  diff output.txt answer.txt || break
done
