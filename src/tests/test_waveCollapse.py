
import WaveCollapseInterface as WCI

#ensure reassigned dont cause seg faults
def test_Initiation():
    
    
    constraints = [None]*2

    constraints[0] = WCI.Constraint(WCI.Type.CORD, 1, 0, [1, 0], False)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, 1, 0, [-1, 0], False)

    state = [.898, .1, .001, .001]
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, -1)

    waveCollapse = WCI.WaveCollapse(state, constraints, 10, -1)

    waveCollapse.generateChunk(0, 0, True)
    waveCollapse.generateChunk(-1, 0, True)

    chunk = waveCollapse.getChunk(0, 0)
    chunk = waveCollapse.getChunk(-1, 0)

    tile = chunk.getTile(0, 0)
    tile = chunk.getTile(1, 0)
    
    assert True


def test_fullCollapse():
    constraints = [None]*4

    constraints[0] = WCI.Constraint(WCI.Type.CORD, 0, 1, [1, 0], False)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, 0, 1, [-1, 0], False)
    constraints[2] = WCI.Constraint(WCI.Type.CORD, 0, 1, [0, 1], False)
    constraints[3] = WCI.Constraint(WCI.Type.CORD, 0, 1, [0, -1], False)

    state = [.99, .01]
    
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, -1)

    #waveCollapse.setSeed(1)

    waveCollapse.generateChunk(0, 0, True)

    for x in range(15):
        for y in range(15):
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsed
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState == 0


def test_collapseTo():
    constraints = [None]*4

    constraints[0] = WCI.Constraint(WCI.Type.CORD, 0, 1, [1, 0], True)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, 0, 1, [-1, 0], True)
    constraints[2] = WCI.Constraint(WCI.Type.CORD, 0, 1, [0, 1], True)
    constraints[3] = WCI.Constraint(WCI.Type.CORD, 0, 1, [0, -1], True)

    state = [.99, .01]
    
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, 1)

    #waveCollapse.setSeed(1)

    waveCollapse.generateChunk(0, 0, True)

    for x in range(15):
        for y in range(15):
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsed
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState == 1

