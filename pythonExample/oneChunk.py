

import WaveCollapseInterface as WCI
import pygame

WIDTH = 20


if __name__ == "__main__":
    screenDimensions = [1000, 1000]
    screen = pygame.display.set_mode(screenDimensions)

    # these constraints try to make a tree
    constraints = [None]*16

    #runs quite slowly

    #creates a tree 'seed'
    constraints[0] = WCI.Constraint(WCI.Type.SQUARE, [(3, 5, 0)], 0, False)

    #creates a tree 'trunk'
    constraints[1] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 0)], 1, True)
    constraints[2] = WCI.Constraint(WCI.Type.CORD, [(0, 2, 0)], 1, True)
    constraints[3] = WCI.Constraint(WCI.Type.CORD, [(0, 3, 0)], 2, True)

    constraints[4] = WCI.Constraint(WCI.Type.CORD, [(1, 1, 2)], 1, False)
    constraints[5] = WCI.Constraint(WCI.Type.CORD, [(-1, 1, 2)], 1, False)
    constraints[6] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 2)], 1, False)

    # trunk splits into branches
    # can either collapse to more trunk or to leaves
    constraints[7] = WCI.Constraint(WCI.Type.CORD, [(1, 1, 2)], 5, False)
    constraints[8] = WCI.Constraint(WCI.Type.CORD, [(-1, 1, 2)], 5, False)
    constraints[9] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 2)], 5, False)

    constraints[10] = WCI.Constraint(WCI.Type.CORD, [(1, 1, 2)], 6, False)
    constraints[11] = WCI.Constraint(WCI.Type.CORD, [(-1, 1, 2)], 6, False)
    constraints[12] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 2)], 6, False)

    constraints[13] = WCI.Constraint(WCI.Type.CORD, [(0, 1, 3)], 4, True)
    constraints[14] = WCI.Constraint(WCI.Type.CORD, [(1, 0, 3)], 4, True)
    constraints[15] = WCI.Constraint(WCI.Type.CORD, [(-1, 0, 3)], 4, True)

    # sets states
    state = [.01, .01, .01, .01, .01, .4, .4]

    #size 15 chunk
    #collapses to 0 state to create grid first
    waveCollapse = WCI.WaveCollapse(state, constraints, 30, 0)
    waveCollapse.generateChunk(0, 0, True)

    # gets chunk
    chunk = waveCollapse.getChunk(0, 0)

    # gnerates the chunk
    xPosition = 0
    yPosition = 0
    collapse = True
    waveCollapse.generateChunk(xPosition, yPosition, collapse)

    #draws the chunk
    chunk = waveCollapse.getChunk(xPosition, yPosition)

    for x in range(0, waveCollapse.getChunkSize()):
        for y in range(0, waveCollapse.getChunkSize()):

            #iterates through tiles and draws them
            tile = chunk.getTile(x, y)

            color = pygame.color.Color(0, 0, 0)

            if (tile.collapsedState == 0):
                color = pygame.color.Color(105, 50, 4)

            elif (tile.collapsedState == 1):
                color = pygame.color.Color(105, 50, 4)

            elif (tile.collapsedState == 2):
                color = pygame.color.Color(105, 50, 4)

            elif (tile.collapsedState == 3):
                color = pygame.color.Color(105, 50, 4)

            elif (tile.collapsedState == 4):
                color = pygame.color.Color(0, 130, 10)

            pygame.draw.rect(screen, color, ( x * WIDTH, y * WIDTH, WIDTH, WIDTH))
    pygame.display.flip()


    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()


