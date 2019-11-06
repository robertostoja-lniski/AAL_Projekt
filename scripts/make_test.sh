cd ../testing/
rm test*
rm ./test_app/a.out
g++ test_app/test_gen.cpp -o test_app/a.out
./test_app/a.out