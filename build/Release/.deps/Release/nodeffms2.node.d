cmd_Release/nodeffms2.node := c++ -bundle -undefined dynamic_lookup -Wl,-no_pie -Wl,-search_paths_first -mmacosx-version-min=10.7 -arch x86_64 -L./Release  -o Release/nodeffms2.node Release/obj.target/nodeffms2/src/ffms2.o 
