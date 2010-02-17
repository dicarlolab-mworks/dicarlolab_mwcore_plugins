DEFAULT_CONFIG = "Debug"

BUILD_PLUGIN = \
	cd $(1) && \
	xcodebuild clean -alltargets -configuration $(DEFAULT_CONFIG) && \
	xcodebuild build -target $(2) -configuration $(DEFAULT_CONFIG) 

all: circle-stimulus fake-monkey itc18 movie rectangle-stimulus

circle-stimulus:
	$(call BUILD_PLUGIN,CircleStimulus,CircleStimulusPlugin)

fake-monkey:
	$(call BUILD_PLUGIN,FakeMonkeyPlugin,FakeMonkeyPlugin)

itc18:
	$(call BUILD_PLUGIN,ITC18Plugin,ITC18Plugin)

movie:
	$(call BUILD_PLUGIN,MoviePlugin,MovieStimulusPlugin)

rectangle-stimulus:
	$(call BUILD_PLUGIN,RectangleStimulus,RectangleStimulusPlugin)
