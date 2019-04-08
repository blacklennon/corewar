mkdir -p correct
mkdir -p tests

rm -rf tests/*.cor
rm -rf correct/*.cor

$correct_asm_path = ../asm

if [ $# -ne 2 ]
then
	printf "asm_checker\tUsage:\n\t\tsh asm_checker [path_to_executable] [path_to_tests_dir]\n";
else
	for f in $2/*.s
	do
		 $1 ${f} >> log
	done
	mv $2/*.cor tests/
	for f in $2/*.s
	do
		 $correct_asm_path ${f} >> log
	done
	mv $2/*.cor correct/
	for f in tests/*.cor
	do
		if [ -f correct/$(printf "${f}" | cut -d '/' -f 2) -a -f correct/$(printf "${f}" | cut -d '/' -f 2) ]
		then
			diff correct/$(printf "${f}" | cut -d '/' -f 2) tests/$(printf "${f}" | cut -d '/' -f 2) > /dev/null
			
			if [ $? -eq 2 ]
			then
				printf "\033[41m Fail\t${f} \033[0m\n"
			else
				printf "\033[42m SUCCESS\t${f} \033[0m\n"
			fi
		fi
	done
	printf "$(ls -l tests/ | wc -l | cut -d ' ' -f 7)/$(ls -l correct/ | wc -l | cut -d ' ' -f 7)\n"
fi
