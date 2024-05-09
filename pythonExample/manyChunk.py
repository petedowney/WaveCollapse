
import WaveCollapseInterface as WCI

import pygame

WIDTH = 32
CHUNKWIDTH = (WIDTH * 15)

camera = [0, 0]
screenDimensions = [1000, 1000]

waveCollapse = None

counter = 0

screen = pygame.display.set_mode(screenDimensions)

def keyUpdate():
    
    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT]:
        camera[0] -= 10
    if keys[pygame.K_RIGHT]:
        camera[0] += 10
    if keys[pygame.K_UP]:
        camera[1] -= 10
    if keys[pygame.K_DOWN]:
        camera[1] += 10

    if keys[pygame.K_ESCAPE]:
        pygame.quit()
        exit(0)

    pygame.event.pump() 
    



def update():
    keyUpdate()

    # generates tiles based on camera positions converts camera cord chunk cords
    for x in range(-1, ((int)(screenDimensions[0] / CHUNKWIDTH) + 1)):
        x2 = (int)(x + camera[0] / CHUNKWIDTH)
        for y in range(-1, ((int)(screenDimensions[1] / CHUNKWIDTH) + 1)):
            y2 = (int)(y + camera[1] / CHUNKWIDTH)

            # if the chunk does not exist generate it
            if not waveCollapse.containsChunk(x2, y2):
                waveCollapse.generateChunk(x2, y2, True)

    
def render():

    # iterates through x chunks
    for chunkX in range(-1, (int)(screenDimensions[0] / CHUNKWIDTH + 1)):
        chunkX2 = (int)(chunkX + camera[0] / CHUNKWIDTH)
        #corrects for camera


        # iterates through y chunks     
        for chunkY in range(-1, (int)(screenDimensions[1] / CHUNKWIDTH + 1)):
            chunkY2 = (int)(chunkY + camera[1] / CHUNKWIDTH)
            #corrects for camera

            # shouldnt happen just checks if chunk has been generated or not
            if not waveCollapse.containsChunk(chunkX2, chunkY2):
                print("chunk not found?")
                print(chunkX2, chunkY2)
                exit(1)

            # draws all the tiles on the screen
            chunk = waveCollapse.getChunk(chunkX2, chunkY2)
            for x in range(0, waveCollapse.getChunkSize()):
                for y in range(0, waveCollapse.getChunkSize()):

                    # gets tile data
                    tile = chunk.getTile(x, y)
                    
                    # color determined by tile state
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
                    
                    # draws rect
                    pygame.draw.rect(screen, color, (chunkX2 * CHUNKWIDTH + x * WIDTH - camera[0], chunkY2 * CHUNKWIDTH + y * WIDTH - camera[1], WIDTH, WIDTH))
    
    #draws center
    pygame.draw.circle(screen, (255, 0, 0), (screenDimensions[0] / 2, screenDimensions[1] / 2), 10)        

    # updates
    pygame.display.flip()


if __name__ == "__main__":
    
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
    # creates wave collapse
    # size 15 if it can collapse to 0 state it will if not will go based off of probabilities
    waveCollapse = WCI.WaveCollapse(state, constraints, 15, 0)

    while True:
        update()
        render()



    

#WaveCollapseInterface.WaveCollapse.__init__(self, state, constraints, 15)

#wave_collapse = WaveCollapseInterface.WaveCollapse(state, constraints, 15);

