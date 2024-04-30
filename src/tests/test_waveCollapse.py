
import WaveCollapseInterface as WCI

#ensure reassigned dont cause seg faults

def test_Initiation():
    
    
    constraints = [None]*2

    constraints[0] = WCI.Constraint(WCI.Type.CORD, [(1, 0, 0)], 1, False)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, [(-1, 0, 0)], 1, False)

    state = [.898, .1, .001, .001]
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, -1)

    waveCollapse = WCI.WaveCollapse(state, constraints, 10, -1)

    waveCollapse.generateChunk(0, 0, True)
    waveCollapse.generateChunk(-1, 0, True)

    assert waveCollapse.containsChunk(0,0)
    assert waveCollapse.containsChunk(-1,0)
    assert not waveCollapse.containsChunk(1,0)

    chunk = waveCollapse.getChunk(0, 0)
    chunk = waveCollapse.getChunk(-1, 0)

    tile = chunk.getTile(0, 0)
    tile = chunk.getTile(1, 0)
    
    assert True


def test_fullCollapse():
    constraints = [None]*4

    constraints[0] = WCI.Constraint(WCI.Type.CORD, [(1, 0, 0)], 1, False)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, [(-1, 0, 0)], 1, False)
    constraints[2] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 0)], 1, False)
    constraints[3] = WCI.Constraint(WCI.Type.CORD, [(0, -1, 0)], 1, False)

    state = [.99, .01]
    
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, -1)

    waveCollapse.generateChunk(0, 0, True)

    for x in range(15):
        for y in range(15):
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsed
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState == 0
 

def test_collapseTo():
    constraints = [None]*4

    constraints[0] = WCI.Constraint(WCI.Type.CORD, [(1, 0, 0)], 1, False)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, [(-1, 0, 0)], 1, False)
    constraints[2] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 0)], 1, False)
    constraints[3] = WCI.Constraint(WCI.Type.CORD, [(0, -1, 0)], 1, False)

    state = [.999, .001]
    
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, 1)

    waveCollapse.generateChunk(0, 0, True)

    for x in range(15):
        for y in range(15):
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsed
            assert waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState == 1



def test_constraintCollapse():

    constraints = [None]*8

    constraints[0] = WCI.Constraint(WCI.Type.CORD, [(1, 0, 0)], 1, True)
    constraints[1] = WCI.Constraint(WCI.Type.CORD, [(-1, 0, 0)], 1, True)
    constraints[2] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 0)], 1, True)
    constraints[3] = WCI.Constraint(WCI.Type.CORD, [(0, -1, 0)], 1, True)

    constraints[4] = WCI.Constraint(WCI.Type.CORD, [(1, 0, 1)], 0, True)
    constraints[5] = WCI.Constraint(WCI.Type.CORD, [(-1, 0, 1)], 0, True)
    constraints[6] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 1)], 0, True)
    constraints[7] = WCI.Constraint(WCI.Type.CORD, [(0, -1, 1)], 0, True)

    state = [.999, .001]
    
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, 1)

    waveCollapse.generateChunk(0, 0, True)

    for x in range(15):
        for y in range(15):
            
            state = waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState
            opp = 1 - state

            if (x > 0):
                assert waveCollapse.getChunk(0, 0).getTile(x-1, y).collapsedState == opp
            if (x < 14):
                assert waveCollapse.getChunk(0, 0).getTile(x+1, y).collapsedState == opp
            if (y > 0):
                assert waveCollapse.getChunk(0, 0).getTile(x, y-1).collapsedState == opp
            if (y < 14):
                assert waveCollapse.getChunk(0, 0).getTile(x, y+1).collapsedState == opp



def test_Radius():
    
    for radius in range(1, 5):
        constraints = [None]*5

        radius = 1

        constraints[0] = WCI.Constraint(WCI.Type.RADIUS, [(radius, 0, 0)], 0, False)
        constraints[1] = WCI.Constraint(WCI.Type.RADIUS, [(radius, 0, 1)], 1, False)
        constraints[2] = WCI.Constraint(WCI.Type.RADIUS, [(radius, 0, 2)], 2, False)
        constraints[3] = WCI.Constraint(WCI.Type.RADIUS, [(radius, 0, 3)], 3, False)
        constraints[4] = WCI.Constraint(WCI.Type.RADIUS, [(radius, 0, 4)], 4, False)

        state = [.1, .1, .1, .1, .1, .5]
        
        waveCollapse = WCI.WaveCollapse(state, constraints, 10 + radius * 2, -1)

        waveCollapse.generateChunk(0, 0, True)

        for x in range(1, 8):
            for y in range(1, 8):
                
                middle = waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState

                if (middle == 5):
                    continue
                
                for xRad in range(-radius, radius+1):
                    for yRad in range(-radius, radius+1):
                        
                        if (xRad != 0 or yRad != 0) and (xRad**2 + yRad**2 <= radius**2):
                            assert waveCollapse.getChunk(0, 0).getTile(x+xRad, y+yRad).collapsedState != middle


def test_Square():

    for Height in range(1, 5):
        for Width in range(1, 5):
            constraints = [None]*5

            constraints[0] = WCI.Constraint(WCI.Type.SQUARE, [(Width, Height, 0)], 0, False)
            constraints[1] = WCI.Constraint(WCI.Type.SQUARE, [(Width, Height, 1)], 1, False)
            constraints[2] = WCI.Constraint(WCI.Type.SQUARE, [(Width, Height, 2)], 2, False)
            constraints[3] = WCI.Constraint(WCI.Type.SQUARE, [(Width, Height, 3)], 3, False)
            constraints[4] = WCI.Constraint(WCI.Type.SQUARE, [(Width, Height, 4)], 4, False)

            state = [.1, .1, .1, .1, .1, .5]
            
            waveCollapse = WCI.WaveCollapse(state, constraints, 12, -1)

            waveCollapse.generateChunk(0, 0, True)

            for x in range(Width, 10-Width):
                for y in range(Height, 10-Height):
                    
                    middle = waveCollapse.getChunk(0, 0).getTile(x, y).collapsedState

                    if (middle == 5):
                        continue
                    
                    for xRad in range(-Width, Width-1):
                        for yRad in range(-Height, Height-1):
                            if ((xRad != 0 or yRad != 0)):
                                assert waveCollapse.getChunk(0, 0).getTile(x+xRad, y+yRad).collapsedState != middle
                                