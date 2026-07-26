./calc 3 4 > got.txt 
CAT_EXIT_CODE=$?

echo 7 > expected.txt

if [ $CAT_EXIT_CODE -ne 0 ]; then
    echo "$0: wrong exit code $CAT_EXIT_CODE"
    rm expected.txt
    rm got.txt

    # Report failure to the calling script and exit.
    exit 1
fi

# Check program output
# Complain if it's unexpected.
diff -u expected.txt got.txt
if [ $? -ne 0 ]; then
    # message on failure
    echo "wrong output"
    rm expected.txt
    rm got.txt

    # Report failure to the calling and exit.cript.
    exit 1
fi

# We made it this far.
# Celebrate!
echo "PASS"

# Remove temporary files.
rm expected.txt
rm got.txt

# Report success to the calling and exit.cript.
exit 0
