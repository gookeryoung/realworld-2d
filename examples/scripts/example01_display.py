import assets
import display
#import game_event

surface = 0

display.init()
assets.init()

def on_render():
    display.blit_surface(surface, 0, 0)
#    print surface
    display.flip()

def main_func():
    display.setvideomode(800, 600, False)
    display.setcaption('Example01')

    surface = assets.load_surface("background.png")
    print 'key number: ', surface
#    print surface

