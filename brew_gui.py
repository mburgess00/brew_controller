#!/usr/bin/env python3
from guizero import App, Text, Slider, Combo, PushButton, Box, Picture

pause = True

def readsensors():
    return {"hlt" : 160, "rims" : 152, "bk" : 75}

def handlepause():
    global pause
    global pauseState
    print("Pause Button pressed")
    if pause:
        print("running")
        pause = not pause
        pauseState.value=("Running")
        hltFlame.visible=True
        rimsFlame.visible=True
        bkFlame.visible=True
    else:
        print("pausing")
        pause = not pause
        pauseState.value=("Paused")
        hltFlame.visible=False
        rimsFlame.visible=False
        bkFlame.visible=False
    return

app = App(title="Brew GUI", width=1280, height=768, layout="grid")
vertPad = Picture(app, image="blank_vert.gif", grid=[0,0])

hltBox = Box(app, layout="grid", grid=[1,0])
hltPad = Picture(hltBox, image="blank.gif", grid=[0,0])
hltTitle = Text(hltBox, text="HLT", grid=[0,1], align="top")
hltText = Text(hltBox, text="180", grid=[0,2], align="top")
hltSlider = Slider(hltBox, start=212, end=100, horizontal=False, grid=[0,3], align="top")
hltSlider.tk.config(length=500, width=50)
hltFlamePad = Picture(hltBox, image="blank_flame.gif", grid=[0,4])
hltFlame = Picture(hltBox, image="flame.gif", grid=[0,4])

rimsBox = Box(app, layout="grid", grid=[2,0])
rimsPad = Picture(rimsBox, image="blank.gif", grid=[0,0])
rimsTitle = Text(rimsBox, text="RIMS", grid=[0,1], align="top")
rimsText = Text(rimsBox, text="180", grid=[0,2], align="top")
rimsSlider = Slider(rimsBox, start=212, end=100, horizontal=False, grid=[0,3], align="top")
rimsSlider.tk.config(length=500, width=50)
rimsFlamePad = Picture(rimsBox, image="blank_flame.gif", grid=[0,4])
rimsFlame = Picture(rimsBox, image="flame.gif", grid=[0,4])

bkBox = Box(app, layout="grid", grid=[3,0])
bkPad = Picture(bkBox, image="blank.gif", grid=[0,0])
bkTitle = Text(bkBox, text="BK", grid=[0,1], align="top")
bkText = Text(bkBox, text="75", grid=[0,2], align="top")
bkSlider = Slider(bkBox, start=100, end=0, horizontal=False, grid=[0,3], align="top")
bkSlider.tk.config(length=500, width=50)
bkFlamePad = Picture(bkBox, image="blank_flame.gif", grid=[0,4])
bkFlame = Picture(bkBox, image="flame.gif", grid=[0,4])

modeBox = Box(app, layout="grid", grid=[4,0])
modePad = Picture(modeBox, image="blank.gif", grid=[0,0])
modeTitle = Text(modeBox, text="Mode", grid=[0,0], align="top")
mode = Combo(modeBox, options=["HLT", "RIMS", "BK"], grid=[1,0])
pauseState = Text(modeBox, text="Paused", grid=[0,1])
pauseButton = PushButton(modeBox, icon="pause-play.gif", command=handlepause, grid=[1,1])

hltFlame.visible=False
rimsFlame.visible=False
bkFlame.visible=False

app.display()
