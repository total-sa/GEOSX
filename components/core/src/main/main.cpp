#include "slic/slic.hpp"
#include "slic/GenericOutputStream.hpp"
#include <iostream>

//#include "dataRepository/DataObject.hpp"
#include "PhysicsSolvers/NewtonianMechanics.hpp"

using namespace asctoolkit;


int main()
{

  std::string newName("new solver");
  auto solver = geosx::SolverBase::SolverFactory::Factory(geosx::NewtonianMechanics::CatalogueName(),newName);
  slic::initialize();

  std::string format =  std::string( "***********************************\n" )+
                        std::string( "* <TIMESTAMP>\n\n" ) +
                        std::string( "* LEVEL=<LEVEL>\n" ) +
                        std::string( "* MESSAGE=<MESSAGE>\n" ) +
                        std::string( "* FILE=<FILE>\n" ) +
                        std::string( "* LINE=<LINE>\n" ) +
                        std::string( "***********************************\n" );

  slic::setLoggingMsgLevel( slic::message::Debug );
  slic::addStreamToAllMsgLevels( new slic::GenericOutputStream( &std::cout, format ) );

  SLIC_INFO("you are awesomo\n");
  // STEP 2: shutdown logging environment
  slic::finalize();

  return 0;
}