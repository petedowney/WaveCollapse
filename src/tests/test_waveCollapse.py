
import WaveCollapseInterface as WCI

#ensure reassigned dont cause seg faults
def test_Initiation():
    
    
    constraints = [None]*2

    constraints[0] = WCI.Constraint(WCI.Type.CORD, 1, 0, [1, 0])
    constraints[1] = WCI.Constraint(WCI.Type.CORD, 1, 0, [-1, 0])

    state = [.898, .1, .001, .001]
    waveCollapse = WCI.WaveCollapse(state, constraints, 15)

    waveCollapse = WCI.WaveCollapse(state, constraints, 10)

    waveCollapse.generateChunk(0, 0, True)
    waveCollapse.generateChunk(-1, 0, True)

    chunk = waveCollapse.getChunk(0, 0)
    chunk = waveCollapse.getChunk(-1, 0)

    tile = chunk.getTile(0, 0)
    tile = chunk.getTile(1, 0)
    
    assert True

def test_fullCollapse():
    constraints = [None]*4

    constraints[0] = WCI.Constraint(WCI.Type.CORD, 0, 1, [1, 0])
    constraints[1] = WCI.Constraint(WCI.Type.CORD, 0, 1, [-1, 0])
    constraints[2] = WCI.Constraint(WCI.Type.CORD, 0, 1, [0, 1])
    constraints[3] = WCI.Constraint(WCI.Type.CORD, 0, 1, [0, -1])

    state = [.99, .01]
    
    waveCollapse = WCI.WaveCollapse(state, constraints, 15)

    #waveCollapse.setSeed(1)

    waveCollapse.generateChunk(0, 0, True)

    waveCollapse.getChunk(0, 0).

    for x in range(15):
        for y in range(15):
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsed
            assert waveCollapse.getChunk(0, 0).getTile(x, y).state[0] >= .9999



    assert True