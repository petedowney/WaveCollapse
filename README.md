WaveCollapse
==============================
[![Wave Collapse CI](https://github.com/petedowney/WaveCollapse/actions/workflows/python-package-conda.yml/badge.svg)](https://github.com/petedowney/WaveCollapse/actions/workflows/python-package-conda.yml)
[![codecov](https://codecov.io/gh/petedowney/WaveCollapse/graph/badge.svg?token=EQYV914TGS)](https://codecov.io/gh/petedowney/WaveCollapse)

Wave Collapse Implements the Wave Collapse algorithm to create a library that can procedurally generate tiles. The library is for python written in C++

The wave collapse algorithm works by first defining a default state - a column vector whose sum is equal to 1. Then this state can be given to an N dimensional tensor of any size. Next, a set of constraints are defined. These constraints entangle the various cell states together. Finally, the system collapses by simply measuring it.

This library implements a 2 dimensional classical version of this algorithm.

## Usage
First download and install the library. Then import WaveCollapseInterface.

To use this library first create a wave collapse object. In order to spread out computational intensity a chunking system has been implemented. The Wavecollapse object will generate discrete chunks. The size of these chunks can be determined by the user. To create these chunks call generateChunk(x, y, true) from the WC object. To create subsequent chunks call this same command at different x and y coordinates. 

Each chunk will in turn have a set of tiles. Each one of these tiles will contain a state. To obtain this state call getChunk(chunkX, chunkY) from the WC object. Then from the chunk call getTile(tileX, tileY). 

It should be noted that there are other methods exposed to the API not listed in this documentation. However, the use of these functions is not recommended.

### Constraint:
The constraint class determines what constraints will be enacted by the collapse.

```python
class Constraint(Type ConstraintType, (int, int, int)[] offsets, int effectedState, bool collapseTo)
```

**ConstraintType:** will determine which type of constraint is used. There are three types. CORD will look at specific relative coordinates to see if their state matches the parameters. SQUARE will look at a square of coordinates centered around the tile to see if any match the parameters. RADIUS will look at a radius of coordinates to see if any match the parameters.


**offsets:** This is an array of tuples. It will require different inputs based on the constraint type.


For CORD the first parameter is x offset, the second parameter is y offset, and the third parameter is which state it needs to match. Each array index represents a different coordinate offset that must be matched in order for the collapse to occur.


For SQUARE the first parameter is half width, the second is half height, and the third is the matching state. It will check all tiles within the square. If one matches the collapse will occur. only the first index of the array is used.


For RADIUS the first parameter is radius, the second is unused, and the third is the matching state. It will check all tiles within the radius. If one matches the collapse will occur. only the first index of the array is used.


**effectedState:** Determines what state will ultimately be affected by the constraint. An index based off of the default state should be used


**collapseTo:** If false and constraint conditions are met will set the affected state to zero. If true and constraint conditions are met will the affected state to one and fully collapse the state.

___
This class is a struct in c++ as such it has no functions however the variables above can be publicly accessed after its creation.
 

### WaveCollapse
```python
class WaveCollapse(float[] STDStates, Constraint[] constraints, int chunkSize, int initCollapse)
```

**STDstates:** the standard state each tile will inherit. It should be an array of floats whose sum adds to one.


**constraints:** An array of constraints. See Constraint section for explanation.


**chunkSize:** How many tiles long a chunk is.


**initCollapse** When the wave collapse must randomly collapse a tile, what state it will prefer to collapse to. Inputting -1 will give no preference.

___
```python
GenerateChunk(int x, int y, bool collapse)
```

Generates a chunk that will be stored within the Wave Collapse object.

**x:** The x coordinate of the chunk.

**y:** The y coordinate of the chunk.

**collapse:** Collapse the chunk during generation or not.


```python
bool collapseChunk(int x, int y)
```

Collapses the chunk if not done during generation.

**x:** The x coordinate of the chunk.

**y:** The y coordinate of the chunk.

returns if the chunk has been successfully collapsed.


```python
bool containsChunk(int x, int y)
```
**x:** The x coordinate of the chunk.

**y:** The y coordinate of the chunk.

returns if the chunk has been generated.


```python
Chunk getChunk(int x, int y)
```
**x:** The x coordinate of the chunk.

**y:** The y coordinate of the chunk.

Returns a pointer to the chunk.


```python
setSeed(int seed)
```
sets a seed for the random function.

**seed:** A seed

```python
int getChunkSize()
```

Returns the size of the chunks as a tile length.



### Chunk
A chunk should not be directly made instead a wave collapse object should be made. Then with this object the GenerateChunk method should be called.

___
```python
Tile getTile(int x, int y)
```
**x:** The x coordinate of the tile within the chunk.

**y:** The y coordinate of the tile within the chunk.

returns a Tile pointer

```python
bool getCollapse()
```
returns if the chunk is entirely collapsed or not.


### Tile
A tile should not be directly made by the user. Instead it should be generated by the chunk object. It has the following variables that can be accessed

**Tile.state:** a float array of the state.

**Tile.collapsed:** a bool that will be true if the tile has been fully collapsed.

**Tile.collapsedState:** if the state has been collapsed it will have the index of the collapsed state. If not it will equal -1.
