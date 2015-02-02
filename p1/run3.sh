#! /bin/tcsh

echo This script assumes that your timetest program is named a.out.
echo The times of the three runs for each ADT are placed in the file \"results\"
echo "File ADT# Time#1   Time#2   Time#3   Ignore" > results

set ADT = 1

while ($ADT < 7)
  set fileNum = 1
  while ($fileNum < 5)
    echo File{$fileNum}.dat > tt.tmp
    echo Running File{$fileNum}.dat three times for ADT $ADT
    repeat 3 echo $ADT >> tt.tmp
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " >> results 
    a.out < tt.tmp | awk '/CPU/ {printf("%s     ", $6)}' >> results
    echo " " >> results
    @ fileNum ++
  end # while more files

  @ ADT ++
end # while more ADTs
