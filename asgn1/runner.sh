#!/bin/bash

# This file tests all bird-counting binaries using student-provided test files.
#
#       Usage:  bash runner.sh
#               bash runner.sh test_name.sh
#
# Place test files in the directory "tests".  The name of each test must
# start with "test_" and end with ".sh".
#
#       tests/test_anything_you_want.sh
#       \_________/\_______________/\_/
#        required     your choice    required
#
# Examples:  test_input1_plus_511a.sh
#            test_input1_plus_511b.sh
#            test_input1_plus_512a.sh
#            test_input1_512b.sh
#            test_input1_with_two_minuses.sh
#
# Each of your tests must end with end with "exit 0" or "exit 1"


# Configure the test script.
REPORT_PASSING_TESTS=1
PRINT_TEST_OUTPUT=0
PRINT_USING_COLOR=1

# Automatically determine which binaries to run.
MACHINE=`uname -m`
KERNEL=`uname -r | sed -e 's/.*-//'`

# Assume Apple laptops.
cat_folder=compiled_cats_arm

# Windows laptops?
if [ $MACHINE = 'x86_64' ]
then
    cat_folder=compiled_cats_x86
fi

# GitHub?
if [ $KERNEL = 'azure' ]
then
    cat_folder=compiled_cats_hub
fi

# For all "cat" binaries
for cat in $(find $cat_folder -name '*cat' | sort); do
    cp $cat calc

    # for all test scripts
    for scriptname in $(find tests -name 'test*.sh' | sort); do
        cp $scriptname current_test.sh

        if [ "$1" = "" ] || [ "tests/$1" = "$scriptname" ]
        then
            # run the test
            err=$(bash current_test.sh 2> /dev/null)

            if [ $? -eq 0 ]
            then
                if [ $REPORT_PASSING_TESTS -eq 1 ] ; then
                    if [ $PRINT_USING_COLOR -eq 1 ] ; then
                        printf "\033[96mPASS:   %-32swith %s\033[0m\n" $cat $scriptname
                        if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                            /usr/bin/echo -e "\033[90mMessage:\n$err\033[0m"
                        fi
                    else
                        printf "PASS:   %-32swith %s\n" $cat $scriptname
                        if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                            echo Message:
                            echo $err
                        fi
                    fi
                fi
            else
                if [ $PRINT_USING_COLOR -eq 1 ] ; then
                    printf "\033[93mFAIL:   %-32swith %s\033[0m\n" $cat $scriptname
                    if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                        /usr/bin/echo -e "\033[90mMessage\n$err\033[0m"
                    fi
                else
                    printf "FAIL:   %-32swith %s\n" $cat $scriptname
                    if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                        echo Message:
                        echo $err
                    fi
                fi
            fi
        fi

        rm current_test.sh
    done
    
    rm calc
done
