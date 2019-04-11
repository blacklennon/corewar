#!/bin/bash

DIFFDIR=diff
DIFF_COUNT=0

rm -rf $DIFFDIR

if [ $# -ne 2 ]
then
	printf "asm_checker\tUsage:\n\t\tsh asm_checker [path_to_executable] [path_to_tests_dir]\n";
else
	FILES=`find $2 -name "*.s" -type f`
	for FILE in $FILES; do
		CORFILE=${FILE%.s}.cor

		# You
		OUT=$($1 $FILE)
		if [ $? -eq 0 ]; then
			COR=$(xxd $CORFILE)
			PASS=1
		else
			PASS=0
		fi

		# Zaz
		OUT_ZAZ=$(../asm $FILE)
		if [ $? -eq 0 ]; then
			COR_ZAZ=$(xxd $CORFILE)
			PASS_ZAZ=1
		else
			PASS_ZAZ=0
		fi

		rm -f $CORFILE

		if [ $PASS -eq 1 -a $PASS_ZAZ -eq 1 ]; then
			DIFF=$(diff <(echo "$COR") <(echo "$COR_ZAZ"))
			echo "$DIFF"
			KO=$?
			#echo "$KO"
		elif [ $PASS -eq 0 -a $PASS_ZAZ -eq 0 ]; then
			KO=0
		else
			KO=1
		fi

		if [ $KO -eq 0 ]; then
			printf "\033[32m%s OK\033[0m\n" "$FILE"
		else
			printf "\033[41m%s FAIL\033[0m\n" "$FILE"
			if [ $PASS -eq 1 -a $PASS_ZAZ -eq 1 ]; then
				mkdir -p $DIFFDIR
				printf "MDR %s RDM\n" "$DIFF"
				echo "$DIFF" > $DIFFDIR/$DIFF_COUNT\_${FILE##*/}
				((DIFF_COUNT++))
			else
				printf " === YOU ===\n%s\n === ZAZ ===\n%s\n\n" "$OUT" "$OUT_ZAZ"
			fi
		fi
	done
fi
