BEGIN {
   count = 0;
   obj = "";
   if (pass == "h") {
      print "#include <stdbool.h>";
   }
   if (pass == "c2") {
      print "\nstatic bool alwaysTrue(void) { return true; }";
      print "\nOBJECT objs[] = {";
   }
}

/^- / {
   outputRecord(",");
   obj = $2;
   prop["condition"]   = "alwaysTrue";
   prop["description"] = "NULL";
   prop["tags"]        = "";
   prop["location"]    = "NULL";
   prop["destination"] = "NULL";
   prop["prospect"]    = "";
   prop["details"]     = "\"You see nothing special.\\n\"";
   prop["contents"]    = "\"You see\"";
   prop["textGo"]      = "\"You can't get much closer than this.\\n\"";
   prop["weight"]      = "99";
   prop["capacity"]    = "0";
   prop["health"]      = "0";
   prop["open"]        = "cannotBeOpened";
   prop["close"]       = "cannotBeClosed";
   prop["lock"]        = "cannotBeLocked";
   prop["unlock"]      = "cannotBeUnlocked";
}

obj && /^[ \t]+[a-z]/ {
   name = $1;
   $1 = "";
   if (name in prop) {
      prop[name] = $0;
      if (/^[ \t]*\{/) {
         prop[name] = name count;
         if (pass == "c1") print "static bool " prop[name] "(void) " $0;
      }
   }
   else if (pass == "c2") {
      print "#error \"" FILENAME " line " NR ": unknown attribute '" name "'\"";
   }
}

!obj && pass == (/^#include/ ? "c1" : "h") {
   print;
}

END {
   outputRecord("\n};");
   if (pass == "h") {
      print "\n#define endOfObjs\t(objs + " count ")";
      print "\n#define validObject(obj)\t" \
            "((obj) != NULL && (*(obj)->condition)())";
      print "\n#define forEachObject(obj)\t" \
            "for (obj = objs; obj < endOfObjs; obj++) if (validObject(obj))";
   }
}

function outputRecord(separator)
{
   if (obj) {
      if (pass == "h") {
         print "#define " obj "\t(objs + " count ")";
      }
      else if (pass == "c1") {
         print "static const char *tags" count "[] = {" prop["tags"] ", NULL};";
      }
      else if (pass == "c2") {
         print "\t{\t/* " count " = " obj " */";
         print "\t\t" prop["condition"] ",";
         print "\t\t" prop["description"] ",";
         print "\t\ttags" count ",";
         print "\t\t" prop["location"] ",";
         print "\t\t" prop["destination"] ",";
         print "\t\t" prop[prop["prospect"] ? "prospect" : "destination"] ",";
         print "\t\t" prop["details"] ",";
         print "\t\t" prop["contents"] ",";
         print "\t\t" prop["textGo"] ",";
         print "\t\t" prop["weight"] ",";
         print "\t\t" prop["capacity"] ",";
         print "\t\t" prop["health"] ",";
         print "\t\t" prop["open"] ",";
         print "\t\t" prop["close"] ",";
         print "\t\t" prop["lock"] ",";
         print "\t\t" prop["unlock"];
         print "\t}" separator;
         delete prop;
      }
      count++;
   }
}
