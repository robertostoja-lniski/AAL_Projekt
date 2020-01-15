#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test

#include <boost/test/unit_test.hpp>
#include "../../include/DataStorage.hpp"
#include "../../include/Graph.hpp"
#include "../../include/GraphHelpClasses.hpp"
#include "../../include/Solver.hpp"
#include "../../include/Worker.hpp"

int add( int i, int j ) { return i+j; }

BOOST_AUTO_TEST_CASE( limit )
{
   DataStorage dataStorage;
   const std::string filename = "../testing/data_example.txt";
   const size_t expectedLimit = 1;

   dataStorage.readData(filename);
   size_t actualLimit = dataStorage.getLimit();

   BOOST_CHECK_EQUAL(actualLimit, expectedLimit);
}

BOOST_AUTO_TEST_CASE( project_num )
{
   DataStorage dataStorage;
   const std::string filename = "../testing/data_example.txt";
   const size_t expectedProjectsNum = 3;

   dataStorage.readData(filename);
   size_t actualProjectsNum = dataStorage.getProjectsNum();

   BOOST_CHECK_EQUAL(actualProjectsNum, expectedProjectsNum);
}

BOOST_AUTO_TEST_CASE( worker_num )
{
   DataStorage dataStorage;
   const std::string filename = "../testing/data_example.txt";
   const size_t expectedWorkerNum = 4;

   dataStorage.readData(filename);
   size_t actualWorkerNum = dataStorage.getWorkersNum();

   BOOST_CHECK_EQUAL(actualWorkerNum, expectedWorkerNum);
}

BOOST_AUTO_TEST_CASE( sector_num )
{
   DataStorage dataStorage;
   const std::string filename = "../testing/data_example.txt";
   const size_t expectedSectorsNum = 3;

   dataStorage.readData(filename);
   size_t actualSectorsNum = dataStorage.getSectorsNum();

   BOOST_CHECK_EQUAL(actualSectorsNum, expectedSectorsNum);
}

BOOST_AUTO_TEST_CASE( get_existing_sector_num )
{
   DataStorage dataStorage;
   const std::string filename = "../testing/data_example.txt";
   const size_t expectedSectorId = 0;

   dataStorage.readData(filename);
   size_t actualSectorId = dataStorage.getSectorId("HR");

   BOOST_CHECK_EQUAL(actualSectorId, expectedSectorId);
}

BOOST_AUTO_TEST_CASE( get_non_existing_sector )
{
  DataStorage dataStorage;
  const std::string filename = "../testing/data_example.txt";
  const size_t expectedSectorId = -1;

  dataStorage.readData(filename);
  size_t actualSectorId = dataStorage.getSectorId("DUMMY");

  BOOST_CHECK_EQUAL(actualSectorId, expectedSectorId);
}

BOOST_AUTO_TEST_CASE( get_sector_name )
{
  DataStorage dataStorage;
  const std::string filename = "../testing/data_example.txt";
  auto expectedSectorName = "HR";

  dataStorage.readData(filename);
  auto actualSectorName = dataStorage.getSectorAt(0);

  BOOST_CHECK_EQUAL(actualSectorName, expectedSectorName);
}

BOOST_AUTO_TEST_CASE( get_project_id )
{
  DataStorage dataStorage;
  const std::string filename = "../testing/data_example.txt";
  auto expectedProjectId = 0;

  dataStorage.readData(filename);
  auto actualProjectId = dataStorage.getProjectId("P1");

  BOOST_CHECK_EQUAL(expectedProjectId, actualProjectId);
}

BOOST_AUTO_TEST_CASE( get_project_at )
{
  DataStorage dataStorage;
  const std::string filename = "../testing/data_example.txt";
  auto expectedProjectName = "P1";

  dataStorage.readData(filename);
  auto actualProjectName = dataStorage.getProjectAt(0);

  BOOST_CHECK_EQUAL(actualProjectName, expectedProjectName);
}

BOOST_AUTO_TEST_CASE( get_sector_name_test )
{
  DataStorage dataStorage;
  const std::string filename = "../testing/data_example.txt";

  dataStorage.readData(filename);
  Worker expectedWorker("Jan", "HR", 0);

  auto actualWorker = dataStorage.getWorkerAt(0);

  // overloading == operator not implemented
  BOOST_CHECK_EQUAL(expectedWorker.getName(), actualWorker.getName());
}

BOOST_AUTO_TEST_CASE( constructing_worker_empty )
{
  Worker emptyWorker;
  const std::string emptyName;
  const std::string emptySector;  
  
  BOOST_CHECK_EQUAL(emptyWorker.getName(), emptyName);
  BOOST_CHECK_EQUAL(emptyWorker.getSector(), emptySector);
}

BOOST_AUTO_TEST_CASE( constructing_worker_nonempty )
{
  const std::string actualName = "worker";
  const std::string actualSector = "sector";
  const int actualId = 100;  

  Worker emptyWorker(actualName, actualSector, actualId);
  BOOST_CHECK_EQUAL(emptyWorker.getSector(), actualSector);
  BOOST_CHECK_EQUAL(emptyWorker.getName(), actualName);
  BOOST_CHECK_EQUAL(emptyWorker.getId(), actualId);
}

BOOST_AUTO_TEST_CASE( checking_graph_size1 )
{
    DataStorage dataStorage;
    dataStorage.addProject("p1");
    dataStorage.addSector("s1");
    Worker worker("w1", "s1", 1);
    worker.addProject("p1");
    dataStorage.addWorker(worker);

    Graph graph;
    graph.generateGraph(dataStorage);
    BOOST_CHECK_EQUAL(graph.getSize(), 5);
}

BOOST_AUTO_TEST_CASE( checking_graph_limit1 )
{
    DataStorage dataStorage;
    dataStorage.addProject("p1");
    dataStorage.addSector("s1");
    Worker worker("w1", "s1", 1);
    worker.addProject("p1");
    dataStorage.addWorker(worker);

    Graph graph;
    graph.generateGraph(dataStorage);
    BOOST_CHECK_EQUAL(graph.getLimit(), 0);
}

BOOST_AUTO_TEST_CASE( checking_graph_size2 )
{
    DataStorage dataStorage;
    dataStorage.addProject("p1");
    dataStorage.addProject("p2");
    dataStorage.addProject("p3");
    dataStorage.addSector("s1");
    dataStorage.addSector("s2");
    dataStorage.addSector("s2");

    Worker worker1("w1", "s1", 1);
    worker1.addProject("p1");
    worker1.addProject("p2");

    Worker worker2("w2", "s2", 2);
    worker2.addProject("p2");
    worker2.addProject("p3");

    Worker worker3("w3", "s2", 3);
    worker3.addProject("p3");
    worker3.addProject("p1");

    dataStorage.addWorker(worker1);
    dataStorage.addWorker(worker2);
    dataStorage.addWorker(worker3);

    Graph graph;
    graph.generateGraph(dataStorage);
    BOOST_CHECK_EQUAL(graph.getSize(), 11);
}

BOOST_AUTO_TEST_CASE( checking_graph_limit2 )
{
    DataStorage dataStorage;
    dataStorage.addProject("p1");
    dataStorage.addProject("p2");
    dataStorage.addProject("p3");
    dataStorage.addSector("s1");
    dataStorage.addSector("s2");
    dataStorage.addSector("s2");

    Worker worker1("w1", "s1", 1);
    worker1.addProject("p1");
    worker1.addProject("p2");

    Worker worker2("w2", "s2", 2);
    worker2.addProject("p2");
    worker2.addProject("p3");

    Worker worker3("w3", "s2", 3);
    worker3.addProject("p3");
    worker3.addProject("p1");

    dataStorage.addWorker(worker1);
    dataStorage.addWorker(worker2);
    dataStorage.addWorker(worker3);

    Graph graph;
    graph.generateGraph(dataStorage);
    BOOST_CHECK_EQUAL(graph.getLimit(), 1);
}

BOOST_AUTO_TEST_CASE( checking_graph_size3 )
{
    DataStorage dataStorage;
    Graph graph;
    graph.generateGraph(dataStorage);
    BOOST_CHECK_EQUAL(graph.getSize(), 0);
}

BOOST_AUTO_TEST_CASE( checking_graph_limit3 )
{
    DataStorage dataStorage;
    Graph graph;
    graph.generateGraph(dataStorage);
    BOOST_CHECK_EQUAL(graph.getLimit(), 0);
}

BOOST_AUTO_TEST_CASE( empty_solver )
{
    DataStorage dataStorage;
    Graph graph;
    graph.generateGraph(dataStorage);
    Solver solver;
    solver.fordFulkerson(graph.getRepresentation(), graph.getSize(), graph.getLimit());
}

