rm ../bin/unit.out
g++ ../testing/unit_tests/test.cpp ../src/Graph.cpp ../src/DataStorage.cpp ../src/Solver.cpp -o ../bin/unit.out -lboost_unit_test_framework
../bin/unit.out
