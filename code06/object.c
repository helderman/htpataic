#include <stdio.h>
#include "object.h"

OBJECT objs[] = {
   {"an open field"  , "field"   , NULL , NULL  },
   {"a little cave"  , "cave"    , NULL , NULL  },
   {"a silver coin"  , "silver"  , field, NULL  },
   {"a gold coin"    , "gold"    , cave , NULL  },
   {"a burly guard"  , "guard"   , field, NULL  },
   {"yourself"       , "yourself", field, NULL  },
   {"a cave entrance", "entrance", field, cave  },
   {"an exit"        , "exit"    , cave , field }
};
