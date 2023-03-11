# Services

These 2 files alone are nothing, but it makes no sense to provide a specific set of services here, to see how one would use the provider and the abstractService class, checkout <https://github.com/BrunoC-L/sfml-rs2d/blob/master/src/server/server/service.h> and some of the services in server or client for example.

The goal is simply to give a few services a way to get eachother by name, it makes it really easy to replace one for your tests! as you can imagine, you can instantiate whatever service you want and make it register instead of the original, as long as it inherits that abstract service class, it will compile just fine, then you can mock every functionality the original service did for that test, well, you get the point I think.
