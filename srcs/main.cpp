#include <iostream>
#include <cstdlib>
#include <queue>

#include "KompexSQLiteException.h"
#include "GDL/ModelException.hpp"
#include "XML/ticpp.h"
#include "Data.hpp"
#include "Core.hpp"

int	main()
{
  try
    {
      Core game;
      game.run();
    }
  catch (gdl::ModelException *e)
    {
      std::cout << e->what() << std::endl;
    }
  catch (Kompex::SQLiteException e)
    {
      std::cout << e.GetString() << std::endl;
    }
  catch (ticpp::Exception e)
    {
      std::cout << e.what() << std::endl;
    }
  return (0);
}
