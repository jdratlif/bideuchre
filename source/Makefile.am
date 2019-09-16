AUTOMAKE_OPTIONS = subdir-objects
EXTRA_DIST = images/*.bmp res/Info.plist

bin_PROGRAMS = bideuchre

bideuchre_SOURCES = AppConstants.hh \
	BidEuchreApp.cc BidEuchreApp.hh \
	model/ModelConstants.hh \
	model/Bid.cc model/Bid.hh \
	model/BidHistory.cc model/BidHistory.hh \
	model/Card.cc model/Card.hh \
	model/Deck.cc model/Deck.hh \
	model/Hand.cc model/Hand.hh \
	model/Play.cc model/Play.hh \
	model/RoundHistory.cc model/RoundHistory.hh \
	model/Score.cc model/Score.hh \
	model/Winner.cc model/Winner.hh \
	engine/AIPlayer.cc engine/AIPlayer.hh \
	engine/Game.cc engine/Game.hh \
	engine/GameThread.cc engine/GameThread.hh \
	engine/Player.cc engine/Player.hh \
	engine/Round.cc engine/Round.hh \
	engine/Trick.cc engine/Trick.hh \
	bridge/Bridge.cc bridge/Bridge.hh \
	ui/UIConstants.hh \
	ui/BidDialog.cc ui/BidDialog.hh \
	ui/EuchreFrame.cc ui/EuchreFrame.hh \
	ui/GamePanel.cc ui/GamePanel.hh \
	ui/GUI.cc ui/GUI.hh \
	ui/GUIPlayer.cc ui/GUIPlayer.hh \
	ui/HelpDialog.cc ui/HelpDialog.hh \
	ui/ScoreDialog.cc ui/ScoreDialog.hh \
	ui/TextPlayer.cc ui/TextPlayer.hh \
	ui/TextUI.cc ui/TextUI.hh \
	ui/UI.cc ui/UI.hh

bideuchre.app: bideuchre res/Info.plist
	-mkdir bideuchre.app
	-mkdir bideuchre.app/Contents
	-mkdir bideuchre.app/Contents/MacOS
	-mkdir bideuchre.app/Contents/Resources
	cp bideuchre bideuchre.app/Contents/MacOS
	cp res/Info.plist bideuchre.app/Contents
	echo -n 'APPL????' > bideuchre.app/Contents/PkgInfo
