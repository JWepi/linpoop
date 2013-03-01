#! /bin/sh
echo "Welcome !"

#while [ true ]
#do
#    echo "Please choose which project you want to run: 1 (?)"
#    read a
#    if [ $a -eq 1 ] #|| [ $a -eq 2 ]
#    then
#	if [ $a -eq 1 ]
#	then
#	    make ? > logfile/Makefile_?_logs
#	    echo "Project $a (?) has been built"
#	fi
#	if [ $a -eq 2 ]
#	then
#	    make TMP > logfile/Makefile_TMP
#	    echo "Project $a (TMP) has been built"
#	fi
#	echo "Logs have been saved in logfile directory"
#	break
#    else
#	echo "Project $a doesn't exist."
#   fi
#done

echo "Write 'go' if you want to start the project"
read b
if [ $b = "go" ]
then
    echo "You chose to start the project !"
    #if [ $a -eq 1 ]
    #then
	./exec/exec
    #fi
#    if [ $a -eq 2 ]
#    then
#	./exec/TMP
#    fi
else
    echo "Nothing more happens"
fi

#if [ $a -eq 1 ] #|| [ $a -eq 2 ]
#then
    make clean >> logfile/Makefile_logs
    echo "Object files have been cleaned"
#fi

echo "Logs have been saved in logfile directory"
