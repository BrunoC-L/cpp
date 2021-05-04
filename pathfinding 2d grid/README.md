# Pathfind

Pathfinding is a touchy subject, do it wrong and it will cripple your performance. I recommend using A*, but this does NOT use A*, instead it replicates the Runescape pathfinding preferences (prefer north vs south or east vs west when give the choice)

This will be hard to copy and paste in your project so I recommend you salvage what you can, the AbstractMap is there so the predicate can recover the tiles from the map.

This idea is general enough because it asks the tile whether or not it can move to its neighbor, you can use your own code in your Tile class to implement your mechanics. Personally I have walls from 0 to 15, 4 bits in binary, representing the 4 sides of the tile and if they have a wall or not. you can look at the canMoveFrom method in tile, which is not too pretty.

As I said, I'm making this available but it's not quite copy-pastable in your code probably, so rather cut and paste what you can if you can
